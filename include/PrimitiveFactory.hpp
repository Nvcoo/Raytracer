/*
** EPITECH PROJECT, 2026
** PrimitiveFactory
** File description:
** PrimitiveFactory
*/
#pragma once

#include <memory>
#include <string>
#include "IPrimitive.hpp"
#include "Color.hpp"
#include "Math.hpp"

namespace RayTracer {

// centralizes construction of all primitive types
// maps (type + parameters) -> real IPrimitive instance
class PrimitiveFactory {
public:
    static std::shared_ptr<IPrimitive> makeSphere(
        const Math::Point3 &center,
        double radius,
        const Color &color);

    static std::shared_ptr<IPrimitive> makePlane(
        const std::string &axis,
        double position,
        const Color &color,
        bool checkerboard);
    
    static std::shared_ptr<IPrimitive> makeCylinder(
        const Math::Point3 &center,
        double radius,
        double height,
        const Color &color,
        const Math::Vector3 &rotation = Math::Vector3(0, 0, 0));
    static std::shared_ptr<IPrimitive> makeCone(
        const Math::Point3 &center,
        double radius,
        double height,
        const Color &color,
        const Math::Vector3 &rotation = Math::Vector3(0, 0, 0));
};

}
