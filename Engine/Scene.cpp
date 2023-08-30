#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include <iostream>
#include "SimpleMath.h"
void Scene::Awake()
{
    for (const shared_ptr<GameObject>& gameObject : _gameObjects)
    {
        gameObject->Awake();
    }
}

void Scene::Start()
{
    for (const shared_ptr<GameObject>& gameObject : _gameObjects)
    {
        gameObject->Start();
    }
}

std::wstring s2ws1(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void Scene::Update()
{
    shared_ptr<GameObject> a[7];
    for (const shared_ptr<GameObject>& gameObject : _gameObjects)
    {
        gameObject->Update();
    }

    for (size_t i = 0; i < 7; i++)
        a[i] = _gameObjects[i + 1];
    
    for (auto target : a)
    {
        for (size_t i = 0; i < 7; i++)
        {
            if (target == a[i])
                continue;
            else
            {
                float mDis = pow(target->GetTransform()->GetLocalPosition().x - a[i]->GetTransform()->GetLocalPosition().x, 2)
                    + pow(target->GetTransform()->GetLocalPosition().y - a[i]->GetTransform()->GetLocalPosition().y, 2)
                    + pow(target->GetTransform()->GetLocalPosition().z - a[i]->GetTransform()->GetLocalPosition().z, 2);
                mDis = sqrt(mDis);
                if (mDis <= target->getRadius() + a[i]->getRadius())// 충돌 검사 + 물리량 업데이트
                {
                    //충돌 지점 계산
                    Vec3 move = a[i]->GetTransform()->GetLocalPosition() - target->GetTransform()->GetLocalPosition();
                    Vec3 hitpoint = target->GetTransform()->GetLocalPosition() + (move * (target->getRadius() / (a[i]->getRadius() + target->getRadius()))); 

                    //자신의 운동량 수정
                    Vec3 a0Nor = (target->GetTransform()->GetLocalPosition() - hitpoint);
                    a0Nor.Normalize();
                    float size = a0Nor.Dot(-(target->getVelocity()));
                    Vec3 temVel = target->getVelocity() + (size * a0Nor);
                    temVel = temVel + (size * a0Nor);
                    Vec3 _vec = temVel + a[i]->getVelocity();
                    _vec.Normalize();
                    target->setVelocity(_vec);
                }
            }
        }
    }
}



void Scene::LateUpdate()
{
    for (const shared_ptr<GameObject>& gameObject : _gameObjects)
    {
        gameObject->LateUpdate();
    }
}

void Scene::FinalUpdate()
{
    for (const shared_ptr<GameObject>& gameObject : _gameObjects)
    {
        gameObject->FinalUpdate();
    }
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
    _gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
    auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
    if (findIt != _gameObjects.end())
    {
        _gameObjects.erase(findIt);
    }
}