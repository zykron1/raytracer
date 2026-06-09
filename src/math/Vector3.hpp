#pragma once

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(float s) const;
	Vector3 operator*(const Vector3& v) const;
    Vector3 operator/(float s) const;

    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator*=(float s);
    Vector3& operator*=(const Vector3& v);
    Vector3& operator/=(float s);

    float dot(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;

    float length() const;
	float lengthSquared() const;
    Vector3 normalized() const;
};
