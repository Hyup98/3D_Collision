#pragma once
#include "Component.h"
#include "Object.h"

class Transform;
class MeshRenderer;
class Camera;
class MonoBehaviour;

class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<Camera> GetCamera();

	void setVelocity(float x, float y, float z);
	void setPosion(float x, float y, float z);
	void setMass(float mass);
	void setRadius(float);

	Vec3 getVelocity() const;
	Vec3 getPosion() const;
	float getMass() const;
	float getRadius() const;


	void AddComponent(shared_ptr<Component> component);

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
	Vec3 mPosion;
	Vec3 mVelocity;
	float mMass;
	float mRadius;
};

