/*
** EPITECH PROJECT, 2026
** main
** File description:
** Raytracer entry point with SFML display
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "../include/Renderer.hpp"
#include "../include/SceneParser.hpp"
#include "../include/SceneLoader.hpp"

int main(int ac, char **av)
{
    if (ac == 2 && std::string(av[1]) == "--help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>\n"
                  << "  SCENE_FILE: scene configuration\n";
        return 0;
    }
    if (ac != 2) {
        std::cerr << "error: invalid args, use --help or provide one scene file\n";
        return 84;
    }

    const std::string scenePath = av[1];

    // parse scene
    RayTracer::SceneParseResult parseResult = RayTracer::SceneParser::parseFile(scenePath);
    if (!parseResult.ok) {
        const RayTracer::SceneParseError &err = parseResult.error;
        std::cerr << "Scene parsing failed: " << err.message
                  << " (key: " << err.key << " line: " << err.line << " col: " << err.column << ")\n";
        return 84;
    }

    const RayTracer::ParsedScene &parsed = parseResult.scene;

    RayTracer::Scene scene = RayTracer::SceneLoader::load(parsed);

    const int width  = scene.camera.resolutionWidth;
    const int height = scene.camera.resolutionHeight;

    std::vector<RayTracer::Color> buffer = RayTracer::Renderer::renderToBuffer(scene);

    // buffer as sfml img
    sf::Image image;
    image.create(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const RayTracer::Color &c = buffer[y * width + x];
            image.setPixel(x, y, sf::Color(
                static_cast<sf::Uint8>(std::clamp(c.r, 0.0, 1.0) * 255.0),
                static_cast<sf::Uint8>(std::clamp(c.g, 0.0, 1.0) * 255.0),
                static_cast<sf::Uint8>(std::clamp(c.b, 0.0, 1.0) * 255.0)
            ));
        }
    }

    image.saveToFile("output.png");
    RayTracer::Renderer::render(scene, "output.ppm");

    // display
    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to create texture from image\n";
        return 84;
    }

    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer Output");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
