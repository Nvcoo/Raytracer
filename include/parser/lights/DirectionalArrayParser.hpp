/*
** EPITECH PROJECT, 2026
** DirectionalArrayParser
** File description:
** DirectionalArrayParser
*/
#pragma once

#include <string>
#include <vector>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Lights {

bool parseDirectionalArray(const std::string &lightsObj, double defaultIntensity,
    std::vector<ParsedDirectionalLight> &directionalLights, SceneParseError &error);

        }
    }
}
