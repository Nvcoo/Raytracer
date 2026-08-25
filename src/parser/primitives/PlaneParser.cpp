/*
** EPITECH PROJECT, 2026
** PlaneParser
** File description:
** PlaneParser
*/

#include "../../../include/parser/primitives/PlaneParser.hpp"
#include "../../../include/parser/primitives/ParseHelpers.hpp"
#include "../../../include/parser/JsonHelper.hpp"
#include <cstddef>
#include <string>

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parsePlane(const std::string &planeObj, ParsedPlane &plane, SceneParseError &error)
{
    // axis: string "X", "Y", or "Z"
    std::size_t axisPos = planeObj.find("\"axis\"");
    if (axisPos == std::string::npos) {
        error.message = "plane axis is required";
        error.key = "primitives.planes.axis";
        return false;
    }
    std::size_t axisColon = planeObj.find(':', axisPos);
    if (axisColon == std::string::npos) {
        error.message = "malformed plane axis field";
        error.key = "primitives.planes.axis";
        return false;
    }
    std::size_t axisIndex = axisColon + 1;
    if (!JsonHelper::tryExtractJsonString(planeObj, axisIndex, plane.axis, error)) {
        error.key = "primitives.planes.axis";
        return false;
    }
    if (plane.axis != "X" && plane.axis != "Y" && plane.axis != "Z") {
        error.message = "plane axis must be 'X', 'Y', or 'Z', got '" + plane.axis + "'";
        error.key = "primitives.planes.axis";
        return false;
    }

    // position: number
    std::size_t posPos = planeObj.find("\"position\"");
    if (posPos == std::string::npos) {
        error.message = "plane position is required";
        error.key = "primitives.planes.position";
        return false;
    }
    std::size_t posColon = planeObj.find(':', posPos);
    if (posColon == std::string::npos) {
        error.message = "malformed plane position field";
        error.key = "primitives.planes.position";
        return false;
    }
    ++posColon;
    if (!JsonHelper::tryExtractJsonNumber(planeObj, posColon, plane.position, error)) {
        error.key = "primitives.planes.position";
        return false;
    }

    if (!parseColor(planeObj, plane.color, "primitives.planes", error))
        return false;

    if (!parseOptionalVec3(planeObj, "translation", plane.translation, "primitives.planes", error))
        return false;
    if (!parseOptionalVec3(planeObj, "rotation", plane.rotation, "primitives.planes", error))
        return false;

    std::size_t boardPos = planeObj.find("\"checkerboard\"");
    if (boardPos != std::string::npos) {
        std::size_t boardColon = planeObj.find(':', boardPos);
        if (boardColon == std::string::npos) {
            error.message = "malformed plane checkerboard field";
            error.key = "primitives.planes.checkerboard";
            return false;
        }
        std::size_t valueStart = boardColon + 1;
        if (!JsonHelper::tryExtractJsonBool(planeObj, valueStart, plane.checkerboard, error)) {
            error.key = "primitives.planes.checkerboard";
            return false;
        }
    }
    return true;
}

        }
    }
}
