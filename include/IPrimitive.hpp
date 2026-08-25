/*
** EPITECH PROJECT, 2026
** IPrimitive
** File description:
** IPrimitive
*/
#pragma once

#include "Ray.hpp"
#include "HitRecord.hpp"

namespace RayTracer {

class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    // uitersect ray with this primitive
    // returns HitRecord with hit=true if ray intersects, false otherwise
    // tMin and tMax define the valid range for intersection parameter t
    virtual HitRecord intersect(const Ray &ray, double tMin, double tMax) const = 0;
};

}
