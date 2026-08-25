/*
** EPITECH PROJECT, 2026
** ConeParser
** File description:
** ConeParser
*/
#pragma once

#include <string>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseCone(const std::string &coneObj, ParsedCone &cone,
               SceneParseError &error);

        }
    }
}
