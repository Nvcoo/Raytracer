/*
** EPITECH PROJECT, 2026
** DirectionalLightParser
** File description:
** DirectionalLightParser
*/
#pragma once

#include <string>
#include "../../SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Lights {

bool parseDirectionVector(const std::string &lightObj, Math::Vector3 &direction, SceneParseError &error);

        }
    }
}
