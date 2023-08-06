#pragma once

struct Vector2
{
    float x, y;

    Vector2()
        : x(0), y(0) {};

    Vector2(float x, float y)
        : x(x), y(y) {};


    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const float& value) const
    {
        return Vector2(x * value, y * value);
    }

    Vector2 operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Vector3
{
    float x, y, z;

    Vector3()
    : x(0), y(0), z(0) {};

    Vector3(float x, float y, float z)
    : x(x), y(y), z(z) {};

    Vector3(Vector2 v2, float z)
    : x(v2.x), y(v2.y), z(z) {};

    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator+(const Vector2& other) const
    {
        return Vector3(x + other.x, y + other.y, z);
    }

    Vector3& operator+=(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector3 operator*(const float& value) const
    {
        return Vector3(x * value, y * value, z * value);
    }

    Vector3 operator*(const Vector3& other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    explicit operator Vector2() const
    {
        return Vector2(x, y);
    }
};

struct Vector4
{
    float x, y, z, w;

    Vector4()
    : x(0), y(0), z(0), w(0) {};

    Vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {};

    Vector4(Vector2 v2, float z, float w)
    : x(v2.x), y(v2.y), z(z), w(w) {};

    Vector4(Vector3 v3, float w)
    : x(v3.x), y(v3.y), z(v3.z), w(w) {};
};