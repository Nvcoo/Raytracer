/*
** EPITECH PROJECT, 2026
** AmbientLight
** File description:
** AmbientLight
*/
#pragma once
#include "ILight.hpp"
#include "Math.hpp"
#include <vector>
#include <memory>

namespace RayTracer {

class AmbientLight : public ILight {
private:
    Math::Vector3 _color;
    double _intensity;

    public:
    AmbientLight(const Math::Vector3 &color, double intensity)
        : _color(color), _intensity(intensity)
    {
    }

    Math::Vector3 contribute(const Math::Point3 &point,
                             const Math::Vector3 &normal,
                             const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override
    {
        (void)point;
        (void)normal;
        (void)primitives;

        Math::Vector3 c = _color * _intensity;
        return Math::Vector3(c.x, c.y, c.z);
    }
};

}
