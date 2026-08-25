/*
** EPITECH PROJECT, 2026
** ConeParser
** File description:
** ConeParser
*/

#include "../../../include/parser/primitives/ConeParser.hpp"
#include "../../../include/parser/primitives/ParseHelpers.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseCone(const std::string &coneObj, ParsedCone &cone, SceneParseError &error)
{
    // center: x, y, z at cone object level
    std::size_t xPos = coneObj.find("\"x\"");
    if (xPos == std::string::npos) {
        error.message = "cone x is required";
        error.key = "primitives.cones.x";
        return false;
    }
    std::size_t xColon = coneObj.find(':', xPos);
    ++xColon;
    if (!JsonHelper::tryExtractJsonNumber(coneObj, xColon, cone.center.x, error)) {
        error.key = "primitives.cones.x";
        return false;
    }

    std::size_t yPos = coneObj.find("\"y\"");
    if (yPos == std::string::npos) {
        error.message = "cone y is required";
        error.key = "primitives.cones.y";
        return false;
    }
    std::size_t yColon = coneObj.find(':', yPos);
    ++yColon;
    if (!JsonHelper::tryExtractJsonNumber(coneObj, yColon, cone.center.y, error)) {
        error.key = "primitives.cones.y";
        return false;
    }

    std::size_t zPos = coneObj.find("\"z\"");
    if (zPos == std::string::npos) {
        error.message = "cone z is required";
        error.key = "primitives.cones.z";
        return false;
    }
    std::size_t zColon = coneObj.find(':', zPos);
    ++zColon;
    if (!JsonHelper::tryExtractJsonNumber(coneObj, zColon, cone.center.z, error)) {
        error.key = "primitives.cones.z";
        return false;
    }

    // radius: "r" must appear before the color block to avoid collision with color.r
    std::size_t colorKeyPos = coneObj.find("\"color\"");
    std::size_t rPos = coneObj.find("\"r\"");
    if (rPos == std::string::npos || (colorKeyPos != std::string::npos && rPos > colorKeyPos)) {
        error.message = "cone radius 'r' is required and must appear before the color block";
        error.key = "primitives.cones.r";
        return false;
    }
    std::size_t rColon = coneObj.find(':', rPos);
    ++rColon;
    if (!JsonHelper::tryExtractJsonNumber(coneObj, rColon, cone.radius, error)) {
        error.key = "primitives.cones.r";
        return false;
    }
    if (cone.radius <= 0.0) {
        error.message = "cone radius must be greater than 0";
        error.key = "primitives.cones.r";
        return false;
    }

    // height: "h" key, unique, no collision risk
    std::size_t hPos = coneObj.find("\"h\"");
    if (hPos == std::string::npos) {
        error.message = "cone height 'h' is required";
        error.key = "primitives.cones.h";
        return false;
    }
    std::size_t hColon = coneObj.find(':', hPos);
    ++hColon;
    if (!JsonHelper::tryExtractJsonNumber(coneObj, hColon, cone.height, error)) {
        error.key = "primitives.cones.h";
        return false;
    }
    if (cone.height <= 0.0) {
        error.message = "cone height must be greater than 0";
        error.key = "primitives.cones.h";
        return false;
    }

    if (!parseColor(coneObj, cone.color, "primitives.cones", error))
        return false;

    if (!parseOptionalVec3(coneObj, "translation", cone.translation, "primitives.cones", error))
        return false;
    if (!parseOptionalVec3(coneObj, "rotation", cone.rotation, "primitives.cones", error))
        return false;

    return true;
}

        }
    }
}
