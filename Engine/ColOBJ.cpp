#include "pch.h"
#include "ColOBJ.h"

ColOBJ::ColOBJ()
    : mPosion{ 0.0f, 0.0f, 0.0f }
    , mVelocity{ 0.0f, 0.0f, 0.0f }
    , mMass(0)
    , mRadius(0)
{
}

ColOBJ::~ColOBJ()
{
}

void ColOBJ::Update()
{
    mPosion.x += mVelocity.x;
    mPosion.y += mVelocity.y;
    mPosion.z += mVelocity.z;
}

void ColOBJ::setVelocity(float x, float y, float z)
{
    mVelocity.x = x;
    mVelocity.y = y;
    mVelocity.z = z;
}

void ColOBJ::setPosion(float x, float y, float z)
{
    mPosion.x = x;
    mPosion.y = y;
    mPosion.z = z;
}

void ColOBJ::setMass(float mass)
{
    mMass = mass;
}

void ColOBJ::setRadius(float radius)
{
    mRadius = radius;
}

Vec3 ColOBJ::getVelocity() const
{
    return mVelocity;
}

Vec3 ColOBJ::getPosion() const
{
    return mPosion;
}

float ColOBJ::getMass() const
{
    return mMass;
}

float ColOBJ::getRadius() const
{
    return mRadius;
}
