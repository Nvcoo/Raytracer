/*
** EPITECH PROJECT, 2026
** LightFactory
** File description:
** LightFactory
*/
#pragma once

#include <memory>
#include "ILight.hpp"
#include "Math.hpp"

namespace RayTracer {

// centralizes construction of all light types
// maps (type + parameters) -> real ILight instance
class LightFactory {
public:
// header additions
    static std::shared_ptr<ILight> makeAmbientLight(const Math::Vector3 &color, double intensity);

    static std::shared_ptr<ILight> makeDirectionalLight(const Math::Vector3 &dir, const Math::Vector3 &color, double intensity);

    static std::shared_ptr<ILight> makePointLight(const Math::Point3 &pos, const Math::Vector3 &color, double intensity);

};

}
