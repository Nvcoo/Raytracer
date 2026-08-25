/*
** EPITECH PROJECT, 2026
** DirectionalLight
** File description:
** PointLight
*/

#pragma once
#include "ILight.hpp"
#include "Math.hpp"
#include "Ray.hpp"
#include "IPrimitive.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>

namespace RayTracer {

class PointLight : public ILight {
private:
    Math::Point3 _position;
    Math::Vector3 _color; // RGB 0..1
    double _intensity;

public:
    PointLight(const Math::Point3 &pos, const Math::Vector3 &color, double intensity)
        : _position(pos), _color(color), _intensity(intensity)
    {
    }

    Math::Vector3 contribute(const Math::Point3 &point,
                             const Math::Vector3 &normal,
                             const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override
    {
        Math::Vector3 toLight = _position - point;
        double dist2 = toLight.dot(toLight);
        if (dist2 <= 0.0) return Math::Vector3(0,0,0);

        double dist = std::sqrt(dist2);
        toLight /= dist;

        double ndotl = std::max(0.0, normal.dot(toLight));
        double diffuse = ndotl * _intensity / dist2;
        if (diffuse <= 0.0) return Math::Vector3(0,0,0);

        Math::Point3 origin = point + normal * 1e-6;
        Ray shadowRay(origin, toLight);

        for (const auto &prim : primitives) {
            HitRecord h = prim->intersect(shadowRay, 1e-6, std::max(1e-6, dist - 1e-6));
            if (h.hit) return Math::Vector3(0,0,0);
        }

        return Math::Vector3(_color.x * diffuse, _color.y * diffuse, _color.z * diffuse);
    }
};

}
