cmake_minimum_required(VERSION 3.16)

project(raytracer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

option(RAYTRACER_ENABLE_LIBCONFIGPP "enable libconfig++ scene parsing support" ON)
option(RAYTRACER_ENABLE_SFML "enable SFML display support" ON)

find_library(LIBCONFIGPP_LIBRARY NAMES config++ libconfig++
    PATHS /usr/lib /usr/local/lib
)
find_path(LIBCONFIGPP_INCLUDE_DIR NAMES libconfig.h++
    PATHS /usr/include /usr/local/include
)

# --- SFML ---
if (RAYTRACER_ENABLE_SFML)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
endif()

if (RAYTRACER_ENABLE_LIBCONFIGPP AND (NOT LIBCONFIGPP_LIBRARY OR NOT LIBCONFIGPP_INCLUDE_DIR))
    message(WARNING "libconfig++ not found yet: scene parser support is prepared but not enabled")
endif()

if (RAYTRACER_ENABLE_SFML AND NOT SFML_FOUND)
    message(WARNING "SFML not found yet: display support is prepared but not enabled")
endif()

add_executable(raytracer
    src/main.cpp
    src/Renderer.cpp
    src/SceneLoader.cpp
    src/PrimitiveFactory.cpp
    src/LightFactory.cpp
    src/primitives/Sphere.cpp
    src/primitives/Plane.cpp
    src/primitives/Cylinder.cpp
    src/primitives/Cone.cpp
    src/parser/SceneParser.cpp
    src/parser/CameraParser.cpp
    src/parser/LightsParser.cpp
    src/parser/lights/DirectionalArrayParser.cpp
    src/parser/lights/DirectionalLightParser.cpp
    src/parser/PrimitivesParser.cpp
    src/parser/primitives/ParseHelpers.cpp
    src/parser/primitives/SphereParser.cpp
    src/parser/primitives/PlaneParser.cpp
    src/parser/primitives/CylinderParser.cpp
    src/parser/primitives/ConeParser.cpp
    src/parser/JsonHelper.cpp
)

target_include_directories(raytracer PRIVATE include)
target_compile_options(raytracer PRIVATE -Wall -Wextra -Werror)

# --- LINK SFML ONLY IF ENABLED ---
if (RAYTRACER_ENABLE_SFML AND SFML_FOUND)
    target_link_libraries(raytracer PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
    )
endif()

add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/raytracer
    COMMENT "removing raytracer binary..."
)

add_custom_target(re
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/raytracer
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target raytracer
    COMMENT "rebuilding raytracer from scratch..."
)
