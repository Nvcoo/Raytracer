/*
** EPITECH PROJECT, 2026
** DirectionalArrayParser
** File description:
** DirectionalArrayParser
*/

#include "../../../include/parser/lights/DirectionalArrayParser.hpp"
#include "../../../include/parser/lights/DirectionalLightParser.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Lights {

bool parseDirectionalArray(const std::string &lightsObj, double defaultIntensity,
    std::vector<ParsedDirectionalLight> &directionalLights, SceneParseError &error)
{
    directionalLights.clear();

    std::size_t directionalPos = lightsObj.find("\"directional\"");
    if (directionalPos == std::string::npos)
        return true;

    std::size_t directionalIndex = lightsObj.find(':', directionalPos);
    if (directionalIndex == std::string::npos) {
        error.message = "malformed directional field";
        error.key = "lights.directional";
        return false;
    }
    ++directionalIndex;

    std::string directionalArray;
    if (!JsonHelper::tryExtractJsonArray(lightsObj, directionalIndex, directionalArray, error)) {
        error.key = "lights.directional";
        return false;
    }

    std::size_t scan = 0;
    while (true) {
        std::string lightObj;
        if (!JsonHelper::nextObjectInArray(directionalArray, scan, lightObj, error))
            break;

        ParsedDirectionalLight parsed;
        parsed.intensity = defaultIntensity;

        if (!parseDirectionVector(lightObj, parsed.direction, error))
            return false;

        std::size_t intensityPos = lightObj.find("\"intensity\"");
        if (intensityPos != std::string::npos) {
            std::size_t intensityIndex = lightObj.find(':', intensityPos);
            if (intensityIndex == std::string::npos) {
                error.message = "malformed intensity field";
                error.key = "lights.directional.intensity";
                return false;
            }
            ++intensityIndex;

            if (!JsonHelper::tryExtractJsonNumber(lightObj, intensityIndex, parsed.intensity, error)) {
                error.key = "lights.directional.intensity";
                return false;
            }
            if (parsed.intensity < 0.0 || parsed.intensity > 1.0) {
                error.message = "directional intensity must be between 0.0 and 1.0";
                error.key = "lights.directional.intensity";
                return false;
            }
        }

        directionalLights.push_back(parsed);
    }

    return true;
}

        }
    }
}
