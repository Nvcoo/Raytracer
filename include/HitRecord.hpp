/*
** EPITECH PROJECT, 2026
** HitRecord
** File description:
** HitRecord
*/
#pragma once

#include "Math.hpp"
#include "Color.hpp"

namespace RayTracer {

class HitRecord {
public:
    Math::Point3 point;
    Math::Vector3 normal;
    double t = 0.0;
    bool hit = false;
    Color color;

    HitRecord() = default;
    HitRecord(const Math::Point3 &hitPoint, const Math::Vector3 &hitNormal,
              double hitT, bool didHit, const Color &surfaceColor = Color())
        : point(hitPoint), normal(hitNormal), t(hitT), hit(didHit), color(surfaceColor)
    {
    }
};

}
