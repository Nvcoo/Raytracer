/*
** EPITECH PROJECT, 2026
** Camera
** File description:
** Camera
*/
#pragma once

#include "Math.hpp"

namespace RayTracer {

class Camera {
public:
    Math::Point3 position;
    Math::Vector3 direction;
    double fieldOfView = 72.0;
    int resolutionWidth = 1280;
    int resolutionHeight = 720;

    Camera() = default;
    Camera(const Math::Point3 &pos, const Math::Vector3 &dir, double fov, int width, int height)
        : position(pos), direction(dir), fieldOfView(fov), resolutionWidth(width), resolutionHeight(height)
    {
    }
};

}
