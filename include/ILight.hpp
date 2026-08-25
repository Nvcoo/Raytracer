/*
** EPITECH PROJECT, 2026
** ILight
** File description:
** ILight
*/
#pragma once

#include <memory>
#include <vector>
#include "Math.hpp"

namespace RayTracer {

class IPrimitive;

class ILight {
public:
    virtual ~ILight() = default;

    virtual Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal,
        const std::vector<std::shared_ptr<IPrimitive>> &primitives) const = 0;
};

}
