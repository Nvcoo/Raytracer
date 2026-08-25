/*
** EPITECH PROJECT, 2026
** SphereParser
** File description:
** SphereParser
*/
#pragma once

#include <string>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseSphere(const std::string &sphereObj, ParsedSphere &sphere,
                 SceneParseError &error);

        }
    }
}
