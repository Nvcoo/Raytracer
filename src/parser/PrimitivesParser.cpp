/*
** EPITECH PROJECT, 2026
** PrimitivesParser
** File description:
** PrimitivesParser
*/

#include "../../include/parser/PrimitivesParser.hpp"
#include "../../include/parser/JsonHelper.hpp"
#include "../../include/parser/primitives/SphereParser.hpp"
#include "../../include/parser/primitives/PlaneParser.hpp"
#include "../../include/parser/primitives/CylinderParser.hpp"
#include "../../include/parser/primitives/ConeParser.hpp"
#include <functional>

namespace RayTracer {
namespace Parser {
namespace {

bool parsePrimitiveArray(const std::string &primitivesObj, const std::string &key,
                         std::function<bool(const std::string &, SceneParseError &)> parseEntry,
                         SceneParseError &error)
{
    std::size_t keyPos = primitivesObj.find("\"" + key + "\"");
    if (keyPos == std::string::npos)
        return true;

    std::size_t colon = primitivesObj.find(':', keyPos);
    if (colon == std::string::npos) {
        error.message = "malformed primitives." + key + " field";
        error.key = "primitives." + key;
        return false;
    }
    std::size_t idx = colon + 1;

    std::string arrayStr;
    if (!JsonHelper::tryExtractJsonArray(primitivesObj, idx, arrayStr, error)) {
        error.key = "primitives." + key;
        return false;
    }

    std::size_t scan = 0;
    while (true) {
        std::string entryObj;
        if (!JsonHelper::nextObjectInArray(arrayStr, scan, entryObj, error))
            break;
        if (!parseEntry(entryObj, error))
            return false;
    }
    return true;
}

}

bool PrimitivesParser::tryParsePrimitives(const std::string &content, ParsedScene &scene, SceneParseError &error)
{
    const std::size_t primitivesPos = content.find("\"primitives\"");
    if (primitivesPos == std::string::npos)
        return true;

    std::size_t colonPos = content.find(':', primitivesPos);
    if (colonPos == std::string::npos || colonPos >= content.size()) {
        error.message = "malformed primitives field";
        error.key = "primitives";
        return false;
    }

    std::string primitivesObj;
    std::size_t objStart = colonPos + 1;
    if (!JsonHelper::tryExtractJsonObject(content, objStart, primitivesObj, error)) {
        error.key = "primitives";
        return false;
    }

    // parse spheres
    if (!parsePrimitiveArray(primitivesObj, "spheres",
        [&scene](const std::string &obj, SceneParseError &err) {
            ParsedSphere sphere;
            if (!Primitives::parseSphere(obj, sphere, err))
                return false;
            scene.spheres.push_back(sphere);
            return true;
        }, error))
        return false;

    // parse planes
    if (!parsePrimitiveArray(primitivesObj, "planes",
        [&scene](const std::string &obj, SceneParseError &err) {
            ParsedPlane plane;
            if (!Primitives::parsePlane(obj, plane, err))
                return false;
            scene.planes.push_back(plane);
            return true;
        }, error))
        return false;

    // parse cylinders
    if (!parsePrimitiveArray(primitivesObj, "cylinders",
        [&scene](const std::string &obj, SceneParseError &err) {
            ParsedCylinder cylinder;
            if (!Primitives::parseCylinder(obj, cylinder, err))
                return false;
            scene.cylinders.push_back(cylinder);
            return true;
        }, error))
        return false;

    // parse cones
    if (!parsePrimitiveArray(primitivesObj, "cones",
        [&scene](const std::string &obj, SceneParseError &err) {
            ParsedCone cone;
            if (!Primitives::parseCone(obj, cone, err))
                return false;
            scene.cones.push_back(cone);
            return true;
        }, error))
        return false;

    return true;
}

    }
}
