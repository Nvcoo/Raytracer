/*
** EPITECH PROJECT, 2026
** PrimitivesParser
** File description:
** PrimitivesParser
*/
#pragma once

#include <string>
#include "../SceneParser.hpp"

namespace RayTracer {
namespace Parser {

class PrimitivesParser {
public:
    static bool tryParsePrimitives(const std::string &content, ParsedScene &scene, SceneParseError &error);
};

    }
}
