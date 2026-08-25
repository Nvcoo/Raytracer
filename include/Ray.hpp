 /*
** EPITECH PROJECT, 2026
** Ray
** File description:
** Ray
*/
#pragma once

#include "Math.hpp"

namespace RayTracer {

class Ray {
public:
    Math::Point3 origin;
    Math::Vector3 direction;

    Ray() = default;
    Ray(const Math::Point3 &rayOrigin, const Math::Vector3 &rayDirection)
        : origin(rayOrigin), direction(rayDirection)
    {
    }
// formula: P(t) = O + tD
    Math::Point3 at(double t) const
    {
        return origin + (direction * t);
    }
};

}