/*
** EPITECH PROJECT, 2026
** Scene
** File description:
** Scene
*/
#pragma once

#include <memory>
#include <vector>
#include "Camera.hpp"
#include "RenderSettings.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"

namespace RayTracer {

class Scene {
public:
    Camera camera;
    RenderSettings settings;
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    std::vector<std::shared_ptr<ILight>> lights;

    Scene() = default;
    Scene(const Camera &cam, const RenderSettings &sett)
        : camera(cam), settings(sett)
    {
    }
};

}
