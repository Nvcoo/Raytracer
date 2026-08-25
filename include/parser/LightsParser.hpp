/*
** EPITECH PROJECT, 2026
** LightsParser
** File description:
** LightsParser
*/
#pragma once

#include <string>
#include "../SceneParser.hpp"

namespace RayTracer {
namespace Parser {

class LightsParser {
public:
    static bool tryParseLights(const std::string &content, ParsedScene &scene, SceneParseError &error);
};

    }
}
