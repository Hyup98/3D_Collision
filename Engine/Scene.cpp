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
	Vec3 a[2];
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Update();
	}

	a[0] = _gameObjects[1]->GetTransform()->GetLocalPosition();
	a[1] = _gameObjects[2]->GetTransform()->GetLocalPosition();
	
	float mDis = pow(a[0].x - a[1].x, 2)
		+ pow(a[0].y - a[1].y, 2)
		+ pow(a[0].z - a[1].z, 2);

	mDis = sqrt(mDis);
	Vec3 move = a[1] - a[0];
	Vec3 hitpoint{ a[0] + (move * _gameObjects[1]->getRadius() / (_gameObjects[2]->getRadius() + _gameObjects[1]->getRadius())) };

	if (mDis <= _gameObjects[2]->getRadius() + _gameObjects[1]->getRadius())// 충돌 검사 + 물리량 업데이트
	{
		//_gameObjects[2]->setVelocity(0.f, -0.5f, 0.f);
		//a[0] 운동부터 수정
		Vec3 a0Nor = (a[0] - hitpoint);
		a0Nor.Normalize();
		float size = a0Nor.Dot(-(_gameObjects[1]->getVelocity()));
		Vec3 temVel = _gameObjects[1]->getVelocity() + (size * a0Nor);
		temVel = temVel + (size * a0Nor);
		_gameObjects[1]->setVelocity(temVel.x, temVel.y, temVel.z);

		//a[1]
		Vec3 a1Nor = (a[1] - hitpoint);
		a1Nor.Normalize();
		size = a0Nor.Dot(-(_gameObjects[2]->getVelocity()));
		temVel = _gameObjects[2]->getVelocity() + (size * a0Nor);
		temVel = (size * a0Nor) + temVel;
		_gameObjects[2]->setVelocity(temVel.x, temVel.y, temVel.z);
		
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