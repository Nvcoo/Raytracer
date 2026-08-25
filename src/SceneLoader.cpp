/*
** EPITECH PROJECT, 2026
** SceneLoader
** File description:
** SceneLoader
*/

#include "../include/SceneLoader.hpp"
#include "../include/SceneBuilder.hpp"
#include "../include/PrimitiveFactory.hpp"
#include "../include/LightFactory.hpp"
#include <iostream>


namespace RayTracer {

namespace {

// colors in the scene file are 0 to 255, normalize to 0 to 1 for rendering math
Color normalizeColor(const ParsedColor &pc)
{
    return Color(pc.r / 255.0, pc.g / 255.0, pc.b / 255.0);
}

}

Scene SceneLoader::load(const ParsedScene &parsed)
{
    SceneBuilder builder;

    // camera: already a fully constructed Camera from the parser
    builder.withCamera(parsed.camera);

    // ambient light, one global ambient term
    if (parsed.ambientLight > 0.0)
        builder.addLight(LightFactory::makeAmbientLight(parsed.ambientColor, parsed.ambientLight));

    // directional lights
     for (const auto &dl : parsed.directionalLights)
        builder.addLight(LightFactory::makeDirectionalLight(dl.direction, dl.color, dl.intensity));

    // point lights
    for (const auto &pl : parsed.pointLights)
        builder.addLight(LightFactory::makePointLight(pl.position, pl.color, pl.intensity));

    // spheres: apply translation to center at load time
    for (const auto &ps : parsed.spheres) {
        const Math::Point3 center(
            ps.center.x + ps.translation.x,
            ps.center.y + ps.translation.y,
            ps.center.z + ps.translation.z);
        builder.addPrimitive(
            PrimitiveFactory::makeSphere(center, ps.radius, normalizeColor(ps.color)));
    }

    // planes: apply translation along the plane's own axis at load time
    for (const auto &pp : parsed.planes) {
        double position = pp.position;
        if (pp.axis == "X")
            position += pp.translation.x;
        else if (pp.axis == "Y")
            position += pp.translation.y;
        else
            position += pp.translation.z;
        builder.addPrimitive(
            PrimitiveFactory::makePlane(pp.axis, position, normalizeColor(pp.color), pp.checkerboard));
    }

    // cylinders: apply translation to center at load time, pass rotation
    for (const auto &pc : parsed.cylinders) {
        const Math::Point3 center(
            pc.center.x + pc.translation.x,
            pc.center.y + pc.translation.y,
            pc.center.z + pc.translation.z);
        builder.addPrimitive(
            PrimitiveFactory::makeCylinder(center, pc.radius, pc.height, normalizeColor(pc.color), pc.rotation));
    }

    // cones: apply translation to center at load time, pass rotation
    for (const auto &pco : parsed.cones) {
        const Math::Point3 center(
            pco.center.x + pco.translation.x,
            pco.center.y + pco.translation.y,
            pco.center.z + pco.translation.z);
        builder.addPrimitive(
            PrimitiveFactory::makeCone(center, pco.radius, pco.height, normalizeColor(pco.color), pco.rotation));
    }

    return builder.build();
}

}
