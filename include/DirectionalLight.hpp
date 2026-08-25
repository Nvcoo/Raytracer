/*
** EPITECH PROJECT, 2026
** DirectionalLight
** File description:
** DirectionalLight
*/
#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "ILight.hpp"
#include "Math.hpp"
#include "Ray.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {

// directional (infinite distant) light, direction points from the light toward the scene TODO
// contribution at a surface point = Lambert diffuse: max(0, dot(normal, -direction)) * intensity
class DirectionalLight : public ILight {
private:
    Math::Vector3 _direction; // normalized, pointing toward scene (from light source)
    Math::Vector3 _color;
    double _intensity;

public:
    DirectionalLight(const Math::Vector3 &dir, const Math::Vector3 &color, double intensity)
        : _direction(dir), _color(color), _intensity(intensity)
    {
    }

    Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override
    {
        // toward light vector = -_direction
        const Math::Vector3 toLight = _direction * -1.0;
        // Lambert diffuse
        double ndotl = std::max(0.0, normal.dot(toLight));
        double diffuse = ndotl * _intensity;
        if (diffuse <= 0.0) //surface faces away from light, no contribution
            return Math::Vector3(0, 0, 0);
        // offset the shadow ray origin slightly along the normal
        // without this, the ray would inmediately re-hit the same surface
        // it came due to floating point imprecision (also called shadow acne apparently)
        // 1e-6 is small enough to be invisible but large enough to avoid acne

        /*const double offset = 1e-6;
        const Math::Point3 shadowOrigin = {
            point.x + normal.x * offset,
            point.y + normal.y * offset,
            point.z + normal.z * offset
        };*/
        Math::Point3 shadowOrigin = point + normal * 1e-6; // <- simpler form

        const Ray shadowRay = { // cast shadow ray towards the light
            shadowOrigin,
            toLight
        };
        // check if any primitive blocks the path to the light
        // 1e9 is used as infinity, any blocker within that distance counts as a shadow
        // we reuse offset as tMin to skip intersecting with itself near the origin
        for (const auto &prim : primitives) {
            HitRecord h = prim->intersect(shadowRay, 1e-6, 1e9);
            if (h.hit) return Math::Vector3(0,0,0);
        }
        return Math::Vector3(_color.x * diffuse, _color.y * diffuse, _color.z * diffuse);
    }
};

}
