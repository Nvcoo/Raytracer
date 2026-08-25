/*
** EPITECH PROJECT, 2026
** CylinderParser
** File description:
** CylinderParser
*/

#include "../../../include/parser/primitives/CylinderParser.hpp"
#include "../../../include/parser/primitives/ParseHelpers.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseCylinder(const std::string &cylObj, ParsedCylinder &cyl, SceneParseError &error)
{
    // center: x, y, z at cylinder object level
    std::size_t xPos = cylObj.find("\"x\"");
    if (xPos == std::string::npos) {
        error.message = "cylinder x is required";
        error.key = "primitives.cylinders.x";
        return false;
    }
    std::size_t xColon = cylObj.find(':', xPos);
    ++xColon;
    if (!JsonHelper::tryExtractJsonNumber(cylObj, xColon, cyl.center.x, error)) {
        error.key = "primitives.cylinders.x";
        return false;
    }

    std::size_t yPos = cylObj.find("\"y\"");
    if (yPos == std::string::npos) {
        error.message = "cylinder y is required";
        error.key = "primitives.cylinders.y";
        return false;
    }
    std::size_t yColon = cylObj.find(':', yPos);
    ++yColon;
    if (!JsonHelper::tryExtractJsonNumber(cylObj, yColon, cyl.center.y, error)) {
        error.key = "primitives.cylinders.y";
        return false;
    }

    std::size_t zPos = cylObj.find("\"z\"");
    if (zPos == std::string::npos) {
        error.message = "cylinder z is required";
        error.key = "primitives.cylinders.z";
        return false;
    }
    std::size_t zColon = cylObj.find(':', zPos);
    ++zColon;
    if (!JsonHelper::tryExtractJsonNumber(cylObj, zColon, cyl.center.z, error)) {
        error.key = "primitives.cylinders.z";
        return false;
    }

    // radius: "r" must appear before the color block to avoid collision with color.r
    std::size_t colorKeyPos = cylObj.find("\"color\"");
    std::size_t rPos = cylObj.find("\"r\"");
    if (rPos == std::string::npos || (colorKeyPos != std::string::npos && rPos > colorKeyPos)) {
        error.message = "cylinder radius 'r' is required and must appear before the color block";
        error.key = "primitives.cylinders.r";
        return false;
    }
    std::size_t rColon = cylObj.find(':', rPos);
    ++rColon;
    if (!JsonHelper::tryExtractJsonNumber(cylObj, rColon, cyl.radius, error)) {
        error.key = "primitives.cylinders.r";
        return false;
    }
    if (cyl.radius <= 0.0) {
        error.message = "cylinder radius must be greater than 0";
        error.key = "primitives.cylinders.r";
        return false;
    }

    // height: "h" key, unique, no collision risk
    std::size_t hPos = cylObj.find("\"h\"");
    if (hPos == std::string::npos) {
        error.message = "cylinder height 'h' is required";
        error.key = "primitives.cylinders.h";
        return false;
    }
    std::size_t hColon = cylObj.find(':', hPos);
    ++hColon;
    if (!JsonHelper::tryExtractJsonNumber(cylObj, hColon, cyl.height, error)) {
        error.key = "primitives.cylinders.h";
        return false;
    }
    if (cyl.height <= 0.0) {
        error.message = "cylinder height must be greater than 0";
        error.key = "primitives.cylinders.h";
        return false;
    }

    if (!parseColor(cylObj, cyl.color, "primitives.cylinders", error))
        return false;

    if (!parseOptionalVec3(cylObj, "translation", cyl.translation, "primitives.cylinders", error))
        return false;
    if (!parseOptionalVec3(cylObj, "rotation", cyl.rotation, "primitives.cylinders", error))
        return false;

    return true;
}

        }
    }
}
