/*
** EPITECH PROJECT, 2026
** CameraParser
** File description:
** CameraParser
*/
#pragma once

#include <string>
#include "../Camera.hpp"
#include "../SceneParser.hpp"

namespace RayTracer {
namespace Parser {

class CameraParser {
public:
    static bool tryParseCamera(const std::string &content, Camera &camera, SceneParseError &error);
};

    }
}
