/*
** EPITECH PROJECT, 2026
** ParseHelpers
** File description:
** ParseHelpers
*/

#include "../../../include/parser/primitives/ParseHelpers.hpp"
#include "../../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseColor(const std::string &obj, ParsedColor &color, const std::string &prefix, SceneParseError &error)
{
    std::size_t colorPos = obj.find("\"color\"");
    if (colorPos == std::string::npos) {
        error.message = prefix + " color is required";
        error.key = prefix + ".color";
        return false;
    }
    std::size_t colorColon = obj.find(':', colorPos);
    if (colorColon == std::string::npos) {
        error.message = "malformed color field in " + prefix;
        error.key = prefix + ".color";
        return false;
    }
    std::size_t colorIndex = colorColon + 1;
    colorIndex = JsonHelper::skipWhitespace(obj, colorIndex);
    if (colorIndex >= obj.size() || obj[colorIndex] != '{') {
        error.message = "color must be an object in " + prefix;
        error.key = prefix + ".color";
        return false;
    }
    std::string colorObj;
    if (!JsonHelper::tryExtractJsonObject(obj, colorIndex, colorObj, error)) {
        error.key = prefix + ".color";
        return false;
    }

    // r channel
    std::size_t rPos = colorObj.find("\"r\"");
    if (rPos == std::string::npos) {
        error.message = prefix + ".color.r is required";
        error.key = prefix + ".color.r";
        return false;
    }
    std::size_t rColon = colorObj.find(':', rPos);
    if (rColon == std::string::npos) {
        error.message = "malformed color.r in " + prefix;
        error.key = prefix + ".color.r";
        return false;
    }
    ++rColon;
    if (!JsonHelper::tryExtractJsonNumber(colorObj, rColon, color.r, error)) {
        error.key = prefix + ".color.r";
        return false;
    }

    // g channel
    std::size_t gPos = colorObj.find("\"g\"");
    if (gPos == std::string::npos) {
        error.message = prefix + ".color.g is required";
        error.key = prefix + ".color.g";
        return false;
    }
    std::size_t gColon = colorObj.find(':', gPos);
    if (gColon == std::string::npos) {
        error.message = "malformed color.g in " + prefix;
        error.key = prefix + ".color.g";
        return false;
    }
    ++gColon;
    if (!JsonHelper::tryExtractJsonNumber(colorObj, gColon, color.g, error)) {
        error.key = prefix + ".color.g";
        return false;
    }

    // b channel
    std::size_t bPos = colorObj.find("\"b\"");
    if (bPos == std::string::npos) {
        error.message = prefix + ".color.b is required";
        error.key = prefix + ".color.b";
        return false;
    }
    std::size_t bColon = colorObj.find(':', bPos);
    if (bColon == std::string::npos) {
        error.message = "malformed color.b in " + prefix;
        error.key = prefix + ".color.b";
        return false;
    }
    ++bColon;
    if (!JsonHelper::tryExtractJsonNumber(colorObj, bColon, color.b, error)) {
        error.key = prefix + ".color.b";
        return false;
    }

    if (color.r < 0.0 || color.r > 255.0 ||
        color.g < 0.0 || color.g > 255.0 ||
        color.b < 0.0 || color.b > 255.0) {
        error.message = "color channels must be in range 0-255 in " + prefix;
        error.key = prefix + ".color";
        return false;
    }
    return true;
}

bool parseOptionalVec3(const std::string &obj, const std::string &key, Math::Vector3 &vec,
                       const std::string &prefix, SceneParseError &error)
{
    std::size_t keyPos = obj.find("\"" + key + "\"");
    if (keyPos == std::string::npos)
        return true;

    std::size_t colon = obj.find(':', keyPos);
    if (colon == std::string::npos) {
        error.message = "malformed " + key + " field in " + prefix;
        error.key = prefix + "." + key;
        return false;
    }
    std::size_t idx = colon + 1;
    idx = JsonHelper::skipWhitespace(obj, idx);
    if (idx >= obj.size() || obj[idx] != '{') {
        error.message = key + " must be an object in " + prefix;
        error.key = prefix + "." + key;
        return false;
    }
    std::string vecStr;
    if (!JsonHelper::tryExtractJsonObject(obj, idx, vecStr, error)) {
        error.key = prefix + "." + key;
        return false;
    }

    std::size_t xPos = vecStr.find("\"x\"");
    if (xPos != std::string::npos) {
        std::size_t xColon = vecStr.find(':', xPos);
        ++xColon;
        if (!JsonHelper::tryExtractJsonNumber(vecStr, xColon, vec.x, error)) {
            error.key = prefix + "." + key + ".x";
            return false;
        }
    }
    std::size_t yPos = vecStr.find("\"y\"");
    if (yPos != std::string::npos) {
        std::size_t yColon = vecStr.find(':', yPos);
        ++yColon;
        if (!JsonHelper::tryExtractJsonNumber(vecStr, yColon, vec.y, error)) {
            error.key = prefix + "." + key + ".y";
            return false;
        }
    }
    std::size_t zPos = vecStr.find("\"z\"");
    if (zPos != std::string::npos) {
        std::size_t zColon = vecStr.find(':', zPos);
        ++zColon;
        if (!JsonHelper::tryExtractJsonNumber(vecStr, zColon, vec.z, error)) {
            error.key = prefix + "." + key + ".z";
            return false;
        }
    }
    return true;
}

        }
    }
}
