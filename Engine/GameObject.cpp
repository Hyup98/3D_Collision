#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MonoBehaviour.h"
#include <iostream>

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{

}

GameObject::~GameObject()
{

}

void GameObject::Awake()
{
    for (shared_ptr<Component>& component : _components)
    {
        if (component)
            component->Awake();
    }

    for (shared_ptr<MonoBehaviour>& script : _scripts)
    {
        script->Awake();
    }
}

void GameObject::Start()
{
    for (shared_ptr<Component>& component : _components)
    {
        if (component)
            component->Start();
    }

    for (shared_ptr<MonoBehaviour>& script : _scripts)
    {
        script->Start();
    }
}

void GameObject::Update()
{
    for (shared_ptr<Component>& component : _components)
    {
        if (component)
            component->Update();
    }

    for (shared_ptr<MonoBehaviour>& script : _scripts)
    {
        script->Update();
    }
    Vec3 tem = GetTransform()->GetLocalPosition() + mVelocity;

    //화면 밖을 나가려고 하면 충돌 후 안으로 방향 바꾸기
    if (tem.x >= -300 && tem.x <= 300 
        && tem.y >= -200 && tem.y <= 400 
        && tem.z >= 500 && tem.z <= 1010)
    {
        GetTransform()->SetLocalPosition(tem + mVelocity);
    }
    else
    {
        if (tem.x >= -300 && tem.x <= 300
            && tem.y < -200
            && tem.z >= 500 && tem.z <= 1010)//바닥
        {
            Vec3 a0Nor{ 0.f, 1.f, 0.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
        else if (tem.x < -300
            && tem.y >= -200 && tem.y <= 400 
        && tem.z >= 500 && tem.z <= 1010)//벽1
        {
            Vec3 a0Nor{ 1.f, 0.f, 0.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
        else if (tem.x > 300
            && tem.y >= -200 && tem.y <= 400
            && tem.z >= 500 && tem.z <= 1010)//벽2
        {
            Vec3 a0Nor{ -1.f, 0.f, 0.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
        else if (tem.x >= -300 && tem.x <= 300
            && tem.y >= -200 && tem.y <= 400
            && tem.z < 500)//벽1
        {
            Vec3 a0Nor{ 0.f, 0.f, 1.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
        else if (tem.x >= -300 && tem.x <= 300
            && tem.y >= -200 && tem.y <= 400
            && tem.z > 1010)//벽1
        {
            Vec3 a0Nor{ 0.f, 0.f, -1.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
        else//천장
        {
            Vec3 a0Nor{ 0.f, -1.f, 0.f };
            float size = a0Nor.Dot(-(mVelocity));
            Vec3 temVel = mVelocity + (size * a0Nor);
            temVel = temVel + (size * a0Nor);
            mVelocity = temVel;
        }
    }

}

void GameObject::LateUpdate()
{
    for (shared_ptr<Component>& component : _components)
    {
        if (component)
            component->LateUpdate();
    }

    for (shared_ptr<MonoBehaviour>& script : _scripts)
    {
        script->LateUpdate();
    }
}

void GameObject::FinalUpdate()
{
    for (shared_ptr<Component>& component : _components)
    {
        if (component)
            component->FinalUpdate();
    }
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
    uint8 index = static_cast<uint8>(type);
    assert(index < FIXED_COMPONENT_COUNT);
    return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);
    return static_pointer_cast<Transform>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER);
    return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERA);
    return static_pointer_cast<Camera>(component);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
    component->SetGameObject(shared_from_this());

    uint8 index = static_cast<uint8>(component->GetType());
    if (index < FIXED_COMPONENT_COUNT)
    {
        _components[index] = component;
    }
    else
    {
        _scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
    }
}

void GameObject::setVelocity(float x, float y, float z)
{
    mVelocity.x = x;
    mVelocity.y = y;
    mVelocity.z = z;
}

void GameObject::setVelocity(Vec3 vel)
{
    mVelocity = vel;
}

void GameObject::setPosion(float x, float y, float z)
{
    mPosion.x = x;
    mPosion.y = y;
    mPosion.z = z;
}

void GameObject::setPosion(Vec3 pos)
{
    mPosion = pos;
}

void GameObject::setMass(float mass)
{
    mMass = mass;
}

void GameObject::setRadius(float radius)
{
    mRadius = radius;
}

Vec3 GameObject::getVelocity() const
{
    return mVelocity;
}

Vec3 GameObject::getPosion() const
{
    return mPosion;
}

float GameObject::getMass() const
{
    return mMass;
}

float GameObject::getRadius() const
{
    return mRadius;
}