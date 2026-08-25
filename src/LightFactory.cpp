/*
** EPITECH PROJECT, 2026
** LightFactory
** File description:
** LightFactory
*/

#include "../include/LightFactory.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/PointLight.hpp"
namespace RayTracer {

std::shared_ptr<ILight> LightFactory::makeAmbientLight(const Math::Vector3 &color, double intensity)
{
    return std::make_shared<AmbientLight>(color, intensity);
}

std::shared_ptr<ILight> LightFactory::makeDirectionalLight(const Math::Vector3 &dir, const Math::Vector3 &color, double intensity)
{
    return std::make_shared<DirectionalLight>(dir, color, intensity);
}

std::shared_ptr<ILight> LightFactory::makePointLight(const Math::Point3 &pos, const Math::Vector3 &color, double intensity)
{
    return std::make_shared<PointLight>(pos, color, intensity);
}


}
