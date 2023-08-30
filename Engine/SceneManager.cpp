#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"

#include "TestCameraScript.h"
#include "Resources.h"

void SceneManager::Update()
{
    if (_activeScene == nullptr)
        return;

    _activeScene->Update();
    _activeScene->LateUpdate();
    _activeScene->FinalUpdate();
}


void SceneManager::Render()
{
    if (_activeScene == nullptr)
        return;

    const vector<shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
    for (auto& gameObject : gameObjects)
    {
        if (gameObject->GetCamera() == nullptr)
            continue;

        gameObject->GetCamera()->Render();
    }
}

void SceneManager::LoadScene(wstring sceneName)
{
    _activeScene = LoadTestScene();
    _activeScene->Awake();
    _activeScene->Start();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
    shared_ptr<Scene> scene = make_shared<Scene>();

#pragma region Camera
    shared_ptr<GameObject> camera = make_shared<GameObject>();
    camera->AddComponent(make_shared<Transform>());
    camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, FOV=45도
    camera->AddComponent(make_shared<TestCameraScript>());
    camera->GetTransform()->SetLocalPosition(Vec3(0.f, 100.f, 0.f));
    scene->AddGameObject(camera);
#pragma endregion

#pragma region sphere1
    {
        shared_ptr<GameObject> sphere1 = make_shared<GameObject>();
        sphere1->AddComponent(make_shared<Transform>());
        sphere1->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere1->GetTransform()->SetLocalPosition(Vec3(-200.f, -100.f, 500.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere1->setVelocity(1.f, 0.5f, -2.f);
        sphere1->setRadius(40.f);
        sphere1->AddComponent(meshRenderer);
        scene->AddGameObject(sphere1);
    }
#pragma endregion

#pragma region Sphere2
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(-100.f, -10.f, 700.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(0.5f, 1.f, 0.5f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere3
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(0.f, -10.f, 500.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(0.5f, -1.f, 0.3f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere4
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -1000.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(-0.8f, -1.f, 0.5f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere5
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(100.f, 100.f, 700.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(1.f, -1.f, -0.5f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere6
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(150.f, 100.f, 800.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(1.f, 0.6f, 0.2f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere7
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(200.f, -200.f, 900.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(-0.2f, -0.3f, -0.4f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion

#pragma region Sphere8
    {
        shared_ptr<GameObject> sphere2 = make_shared<GameObject>();
        sphere2->AddComponent(make_shared<Transform>());
        sphere2->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
        sphere2->GetTransform()->SetLocalPosition(Vec3(-200.f, 200.f, 600.f));
        shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
        {
            shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
            meshRenderer->SetMesh(sphereMesh);
        }
        {
            shared_ptr<Shader> shader = make_shared<Shader>();
            shared_ptr<Texture> texture = make_shared<Texture>();
            shader->Init(L"..\\Resources\\Shader\\default.hlsli");
            texture->Init(L"..\\Resources\\Texture\\대리석.jpg");
            shared_ptr<Material> material = make_shared<Material>();
            material->SetShader(shader);
            material->SetTexture(0, texture);
            meshRenderer->SetMaterial(material);
        }
        sphere2->setVelocity(0.5f, 1.f, 4.f);
        sphere2->setRadius(40.f);
        sphere2->AddComponent(meshRenderer);

        scene->AddGameObject(sphere2);
    }
#pragma endregion
    return scene;
}