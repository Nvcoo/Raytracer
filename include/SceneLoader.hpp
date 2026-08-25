/*
** EPITECH PROJECT, 2026
** SceneLoader
** File description:
** SceneLoader
*/
#pragma once

#include <string>
#include "Scene.hpp"
#include "SceneParser.hpp"

namespace RayTracer {

// converts a ParsedScene into Scene ready for render       factoie
// and SceneBuilder,
// applies translation to primitive positions at load time NOT SURE
class SceneLoader {
public:
    static Scene load(const ParsedScene &parsed);
};

}
