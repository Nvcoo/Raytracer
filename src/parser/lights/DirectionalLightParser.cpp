/*
** EPITECH PROJECT, 2026
** DirectionalLightParser
** File description:
** DirectionalLightParser
*/

#include "../../../include/parser/lights/DirectionalLightParser.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Lights {

bool parseDirectionVector(const std::string &lightObj, Math::Vector3 &direction, SceneParseError &error)
{
    std::size_t xPos = lightObj.find("\"x\"");
    std::size_t yPos = lightObj.find("\"y\"");
    std::size_t zPos = lightObj.find("\"z\"");

    if (xPos == std::string::npos || yPos == std::string::npos || zPos == std::string::npos) {
        error.message = "directional light must contain x, y and z";
        error.key = "lights.directional";
        return false;
    }

    std::size_t xIndex = lightObj.find(':', xPos);
    std::size_t yIndex = lightObj.find(':', yPos);
    std::size_t zIndex = lightObj.find(':', zPos);

    if (xIndex == std::string::npos || yIndex == std::string::npos || zIndex == std::string::npos) {
        error.message = "malformed directional vector";
        error.key = "lights.directional";
        return false;
    }

    ++xIndex;
    ++yIndex;
    ++zIndex;

    if (!JsonHelper::tryExtractJsonNumber(lightObj, xIndex, direction.x, error)) {
        error.key = "lights.directional.x";
        return false;
    }
    if (!JsonHelper::tryExtractJsonNumber(lightObj, yIndex, direction.y, error)) {
        error.key = "lights.directional.y";
        return false;
    }
    if (!JsonHelper::tryExtractJsonNumber(lightObj, zIndex, direction.z, error)) {
        error.key = "lights.directional.z";
        return false;
    }

    if (direction.length() == 0.0) {
        error.message = "directional light direction must not be 0";
        error.key = "lights.directional";
        return false;
    }

    direction.normalize();
    return true;
}

        }
    }
}
