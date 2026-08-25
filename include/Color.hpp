/*
** EPITECH PROJECT, 2026
** Color
** File description:
** Color
*/
#pragma once

#include "Math.hpp"

namespace RayTracer {

class Color {
public:
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    Color() = default;
    Color(double red, double green, double blue)
        : r(red), g(green), b(blue)
    {
    }

    Color(const Math::Vector3 &vec)
        : r(vec.x), g(vec.y), b(vec.z)
    {
    }

    Math::Vector3 toVector3() const
    {
        return Math::Vector3(r, g, b);
    }
};

}
