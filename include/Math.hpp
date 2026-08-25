/*
** EPITECH PROJECT, 2026
** Math
** File description:
** Math
*/
#pragma once

#include <cmath>

namespace Math {

// offical rotation order for composed transforms: X, then Y, then Z
constexpr const char *rotation_order = "X -> Y -> Z";

class Vector3 {
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vector3() = default;
    Vector3(double xValue, double yValue, double zValue)
        : x(xValue), y(yValue), z(zValue)
    {
    }

    static constexpr double pi = 3.14159265358979323846;

    static double degrees_to_radians(double degrees)
    {
        return degrees * (pi / 180.0);
    }

    // ||v|| = sqrt(x^2 + y^2 + z^2)
    double length() const
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    // v · w = vx * wx + vy * wy + vz * wz
    double dot(const Vector3 &other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    // v / ||v||, with zero vector protection
    Vector3 normalized() const
    {
        const double value = length();

        if (value <= 0.0)
            return Vector3();
        return Vector3(x / value, y / value, z / value);
    }

    Vector3 &normalize()
    {
        const double value = length();

        if (value <= 0.0)
            return *this;
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    Vector3 &rotateX(double degrees)
    {
        const double radians = degrees_to_radians(degrees);
        const double c = std::cos(radians);
        const double s = std::sin(radians);
        const double oldY = y;
        const double oldZ = z;

        y = (oldY * c) - (oldZ * s);
        z = (oldY * s) + (oldZ * c);
        return *this;
    }

    Vector3 &rotateY(double degrees)
    {
        const double radians = degrees_to_radians(degrees);
        const double c = std::cos(radians);
        const double s = std::sin(radians);
        const double oldX = x;
        const double oldZ = z;

        x = (oldX * c) + (oldZ * s);
        z = (-oldX * s) + (oldZ * c);
        return *this;
    }

    Vector3 &rotateZ(double degrees)
    {
        const double radians = degrees_to_radians(degrees);
        const double c = std::cos(radians);
        const double s = std::sin(radians);
        const double oldX = x;
        const double oldY = y;

        x = (oldX * c) - (oldY * s);
        y = (oldX * s) + (oldY * c);
        return *this;
    }

    Vector3 &operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 &operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3 &operator/=(const Vector3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3 &operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3 &operator/=(double scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(*this) += other;
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(*this) -= other;
    }

    Vector3 operator*(const Vector3 &other) const
    {
        return Vector3(*this) *= other;
    }

    Vector3 operator/(const Vector3 &other) const
    {
        return Vector3(*this) /= other;
    }

    Vector3 operator*(double scalar) const
    {
        return Vector3(*this) *= scalar;
    }

    Vector3 operator/(double scalar) const
    {
        return Vector3(*this) /= scalar;
    }

    Vector3 cross(const Vector3 &other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }
};

inline Vector3 operator*(double scalar, const Vector3 &vector)
{
    return vector * scalar;
}

class Point3 {
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Point3() = default;
    Point3(double xValue, double yValue, double zValue)
        : x(xValue), y(yValue), z(zValue)
    {
    }

    // P + v = (px + vx, py + vy, pz + vz)
    Point3 &operator+=(const Vector3 &vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    Point3 &translate(const Vector3 &offset)
    {
        return (*this += offset);
    }

    // translate a point by a vector
    Point3 operator+(const Vector3 &vector) const
    {
        return Point3(*this) += vector;
    }

    // Vector from 2 existing points
    Vector3 operator-(const Point3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
};

using Vector3D = Vector3;
using Point3D = Point3;

}