/*
** EPITECH PROJECT, 2026
** SphereParser
** File description:
** SphereParser
*/

#include "../../../include/parser/primitives/SphereParser.hpp"
#include "../../../include/parser/primitives/ParseHelpers.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseSphere(const std::string &sphereObj, ParsedSphere &sphere, SceneParseError &error)
{
    // center: x, y, z at sphere object level
    std::size_t xPos = sphereObj.find("\"x\"");
    if (xPos == std::string::npos) {
        error.message = "sphere x is required";
        error.key = "primitives.spheres.x";
        return false;
    }
    std::size_t xColon = sphereObj.find(':', xPos);
    ++xColon;
    if (!JsonHelper::tryExtractJsonNumber(sphereObj, xColon, sphere.center.x, error)) {
        error.key = "primitives.spheres.x";
        return false;
    }

    std::size_t yPos = sphereObj.find("\"y\"");
    if (yPos == std::string::npos) {
        error.message = "sphere y is required";
        error.key = "primitives.spheres.y";
        return false;
    }
    std::size_t yColon = sphereObj.find(':', yPos);
    ++yColon;
    if (!JsonHelper::tryExtractJsonNumber(sphereObj, yColon, sphere.center.y, error)) {
        error.key = "primitives.spheres.y";
        return false;
    }

    std::size_t zPos = sphereObj.find("\"z\"");
    if (zPos == std::string::npos) {
        error.message = "sphere z is required";
        error.key = "primitives.spheres.z";
        return false;
    }
    std::size_t zColon = sphereObj.find(':', zPos);
    ++zColon;
    if (!JsonHelper::tryExtractJsonNumber(sphereObj, zColon, sphere.center.z, error)) {
        error.key = "primitives.spheres.z";
        return false;
    }

    // radius: "r" key, must appear before the color block to avoid collision with color.r
    std::size_t colorKeyPos = sphereObj.find("\"color\"");
    std::size_t rPos = sphereObj.find("\"r\"");
    if (rPos == std::string::npos || (colorKeyPos != std::string::npos && rPos > colorKeyPos)) {
        error.message = "sphere radius 'r' is required and must appear before the color block";
        error.key = "primitives.spheres.r";
        return false;
    }
    std::size_t rColon = sphereObj.find(':', rPos);
    ++rColon;
    if (!JsonHelper::tryExtractJsonNumber(sphereObj, rColon, sphere.radius, error)) {
        error.key = "primitives.spheres.r";
        return false;
    }
    if (sphere.radius <= 0.0) {
        error.message = "sphere radius must be greater than 0";
        error.key = "primitives.spheres.r";
        return false;
    }

    if (!parseColor(sphereObj, sphere.color, "primitives.spheres", error))
        return false;

    if (!parseOptionalVec3(sphereObj, "translation", sphere.translation, "primitives.spheres", error))
        return false;
    if (!parseOptionalVec3(sphereObj, "rotation", sphere.rotation, "primitives.spheres", error))
        return false;

    return true;
}

        }
    }
}
