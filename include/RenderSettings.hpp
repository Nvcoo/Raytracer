/*
** EPITECH PROJECT, 2026
** RenderSettings
** File description:
** RenderSettings
*/
#pragma once

#include <algorithm>
#include <thread>
namespace RayTracer {

class RenderSettings {
public:
    int samplesPerPixel = 1;
    int maxBounces = 10;
    double epsilon = 1e-6;
    int threads = std::max(1, static_cast<int>(std::thread::hardware_concurrency()) - 1);

    RenderSettings() = default;
    RenderSettings(int spp, int bounces, double eps, int threadCount)
        : samplesPerPixel(spp), maxBounces(bounces), epsilon(eps), threads(threadCount)
    {
    }
};

}
