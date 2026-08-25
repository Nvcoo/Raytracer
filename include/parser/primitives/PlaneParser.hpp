/*
** EPITECH PROJECT, 2026
** PlaneParser
** File description:
** PlaneParser
*/
#pragma once

#include <string>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parsePlane(const std::string &planeObj, ParsedPlane &plane,
                SceneParseError &error);

        }
    }
}
