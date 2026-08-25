/*
** EPITECH PROJECT, 2026
** SceneParser
** File description:
** SceneParser
*/
#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "Camera.hpp"
#include "Math.hpp"

namespace RayTracer {

class ParsedColor {
public:
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
};

class ParsedSphere {
public:
    Math::Point3 center;
    double radius = 1.0;
    ParsedColor color;
    Math::Vector3 translation;
    Math::Vector3 rotation;
};

class ParsedPlane {
public:
    std::string axis = "Y";
    double position = 0.0;
    ParsedColor color;
    Math::Vector3 translation;
    Math::Vector3 rotation;
    bool checkerboard = false;
};

class ParsedCylinder {
public:
    Math::Point3 center;
    double radius = 1.0;
    double height = 1.0;
    ParsedColor color;
    Math::Vector3 translation;
    Math::Vector3 rotation;
};

class ParsedCone {
public:
    Math::Point3 center;
    double radius = 1.0;
    double height = 1.0;
    ParsedColor color;
    Math::Vector3 translation;
    Math::Vector3 rotation;
};

class ParsedDirectionalLight {
public:
    Math::Vector3 direction;
    double intensity = 1.0;
    Math::Vector3 color = Math::Vector3(1.0, 1.0, 1.0); // default white
};
class ParsedPointLight {
public:
    Math::Point3 position;
    double intensity = 1.0;
    Math::Vector3 color = Math::Vector3(1.0, 1.0, 1.0); // default white
};

class ParsedScene {
public:
    std::string rawContent;
    std::vector<std::string> topLevelKeys;

    Camera camera;

    double ambientLight = 0.0;
    Math::Vector3 ambientColor = Math::Vector3(1.0, 1.0, 1.0); // default white
    std::vector<ParsedDirectionalLight> directionalLights;
    std::vector<ParsedPointLight> pointLights;

    std::vector<ParsedSphere> spheres;
    std::vector<ParsedPlane> planes;
    std::vector<ParsedCylinder> cylinders;
    std::vector<ParsedCone> cones;
};

class SceneParseError {
public:
    std::string message;
    std::size_t line = 1;
    std::size_t column = 1;
    std::string key;

    std::string toString() const;
};

class SceneParseResult {
public:
    bool ok = false;
    ParsedScene scene;
    SceneParseError error;
};

class SceneParser {
public:
    static SceneParseResult parseFile(const std::string &path);
    static SceneParseResult parseText(const std::string &content);
};

}