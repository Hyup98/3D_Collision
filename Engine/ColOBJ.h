#pragma once

class ColOBJ
{
public:
    ColOBJ();
    ~ColOBJ();

    void Update();

    void setVelocity(float x, float y, float z);
    void setPosion(float x, float y, float z);
    void setMass(float mass);
    void setRadius(float);

    Vec3 getVelocity() const;
    Vec3 getPosion() const;
    float getMass() const;
    float getRadius() const;

private:
    Vec3 mPosion;
    Vec3 mVelocity;
    float mMass;
    float mRadius;
};

