/*
** EPITECH PROJECT, 2026
** CylinderParser
** File description:
** CylinderParser
*/
#pragma once

#include <string>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseCylinder(const std::string &cylObj, ParsedCylinder &cyl,
                   SceneParseError &error);

        }
    }
}
