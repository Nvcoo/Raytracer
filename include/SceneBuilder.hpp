/*
** EPITECH PROJECT, 2026
** SceneBuilder
** File description:
** SceneBuilder
*/
#pragma once

#include <memory>
#include "Scene.hpp"

namespace RayTracer {

class SceneBuilder {
private:
    Camera mCamera;
    RenderSettings mSettings;
    std::vector<std::shared_ptr<IPrimitive>> mPrimitives;
    std::vector<std::shared_ptr<ILight>> mLights;

public:
    SceneBuilder() = default;

    SceneBuilder &withCamera(const Camera &camera)
    {
        mCamera = camera;
        return *this;
    }

    SceneBuilder &withRenderSettings(const RenderSettings &settings)
    {
        mSettings = settings;
        return *this;
    }

    SceneBuilder &addPrimitive(std::shared_ptr<IPrimitive> primitive)
    {
        mPrimitives.push_back(primitive);
        return *this;
    }

    SceneBuilder &addLight(std::shared_ptr<ILight> light)
    {
        mLights.push_back(light);
        return *this;
    }

    Scene build()
    {
        Scene scene(mCamera, mSettings);
        scene.primitives = mPrimitives;
        scene.lights = mLights;
        return scene;
    }
};

}
