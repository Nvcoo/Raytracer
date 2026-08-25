/*
** EPITECH PROJECT, 2026
** ParseHelpers
** File description:
** ParseHelpers
*/
#pragma once

#include <string>
#include "../../Math.hpp"
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseColor(const std::string &obj, ParsedColor &color,
                const std::string &prefix, SceneParseError &error);

bool parseOptionalVec3(const std::string &obj, const std::string &key,
                       Math::Vector3 &vec, const std::string &prefix,
                       SceneParseError &error);

        }
    }
}
