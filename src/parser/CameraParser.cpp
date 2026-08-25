/*
** EPITECH PROJECT, 2026
** CameraParser
** File description:
** CameraParser
*/

#include "../../include/parser/CameraParser.hpp"
#include "../../include/parser/JsonHelper.hpp"

namespace RayTracer {
namespace Parser {

bool CameraParser::tryParseCamera(const std::string &content, Camera &camera, SceneParseError &error)
{
    // find camera key
    std::size_t cameraPos = content.find("\"camera\"");
    if (cameraPos == std::string::npos) {
        return true; // camera is optional, use default
    }

    // find the colon after camera
    std::size_t colonPos = content.find(':', cameraPos);
    if (colonPos == std::string::npos || colonPos >= content.size()) {
        error.message = "malformed camera field";
        return false;
    }

    // extract the camera object
    std::string cameraObj;
    std::size_t objStart = colonPos + 1;
    if (!JsonHelper::tryExtractJsonObject(content, objStart, cameraObj, error)) {
        error.key = "camera";
        return false;
    }

    // parse camera object fields: position, fieldOfView, resolution, (optional) direction
    Math::Point3 position(0.0, 0.0, 0.0);
    Math::Vector3 direction(0.0, 0.0, -1.0); // default direction
    double fov = 72.0; // default fov
    int resWidth = 1280, resHeight = 720; // default resolution

    bool hasFov = false, hasResolution = false, hasPosition = false;

    // extract position
    std::size_t posPos = cameraObj.find("\"position\"");
    if (posPos != std::string::npos) {
        std::size_t posColon = cameraObj.find(':', posPos);
        if (posColon != std::string::npos) {
            std::size_t posIndex = posColon + 1;
            posIndex = JsonHelper::skipWhitespace(cameraObj, posIndex);
            if (posIndex < cameraObj.size() && cameraObj[posIndex] == '{') {
                // extract x, y, z from position object
                std::string posStr;
                if (JsonHelper::tryExtractJsonObject(cameraObj, posIndex, posStr, error)) {
                    // parse x
                    std::size_t xPos = posStr.find("\"x\"");
                    if (xPos != std::string::npos) {
                        std::size_t xColon = posStr.find(':', xPos);
                        std::size_t xIndex = xColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(posStr, xIndex, position.x, error)) {
                            error.key = "camera.position.x";
                            return false;
                        }
                    }
                    // parse y
                    std::size_t yPos = posStr.find("\"y\"");
                    if (yPos != std::string::npos) {
                        std::size_t yColon = posStr.find(':', yPos);
                        std::size_t yIndex = yColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(posStr, yIndex, position.y, error)) {
                            error.key = "camera.position.y";
                            return false;
                        }
                    }
                    // parse z
                    std::size_t zPos = posStr.find("\"z\"");
                    if (zPos != std::string::npos) {
                        std::size_t zColon = posStr.find(':', zPos);
                        std::size_t zIndex = zColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(posStr, zIndex, position.z, error)) {
                            error.key = "camera.position.z";
                            return false;
                        }
                    }
                    hasPosition = true;
                }
            }
        }
    }

    if (!hasPosition) {
        error.message = "camera position is required";
        error.key = "camera.position";
        return false;
    }

    // extract fieldOfView
    std::size_t fovPos = cameraObj.find("\"fieldOfView\"");
    if (fovPos != std::string::npos) {
        std::size_t fovColon = cameraObj.find(':', fovPos);
        if (fovColon != std::string::npos) {
            std::size_t fovIndex = fovColon + 1;
            if (!JsonHelper::tryExtractJsonNumber(cameraObj, fovIndex, fov, error)) {
                error.key = "camera.fieldOfView";
                return false;
            }
            hasFov = true;
        }
    }

    if (!hasFov) {
        error.message = "camera fieldOfView is required";
        error.key = "camera.fieldOfView";
        return false;
    }

    // validate fov range 1.0 to 180.0
    if (fov < 1.0 || fov > 180.0) {
        error.message = "fieldOfView must be between 1.0 and 180.0 degrees";
        error.key = "camera.fieldOfView";
        return false;
    }

    // extract resolution
    std::size_t resPos = cameraObj.find("\"resolution\"");
    if (resPos != std::string::npos) {
        std::size_t resColon = cameraObj.find(':', resPos);
        if (resColon != std::string::npos) {
            std::size_t resIndex = resColon + 1;
            resIndex = JsonHelper::skipWhitespace(cameraObj, resIndex);
            if (resIndex < cameraObj.size() && cameraObj[resIndex] == '{') {
                std::string resStr;
                if (JsonHelper::tryExtractJsonObject(cameraObj, resIndex, resStr, error)) {
                    // parse width
                    std::size_t widthPos = resStr.find("\"width\"");
                    if (widthPos != std::string::npos) {
                        std::size_t widthColon = resStr.find(':', widthPos);
                        std::size_t widthIndex = widthColon + 1;
                        double w = 0;
                        if (!JsonHelper::tryExtractJsonNumber(resStr, widthIndex, w, error)) {
                            error.key = "camera.resolution.width";
                            return false;
                        }
                        resWidth = static_cast<int>(w);
                    }
                    // parse height
                    std::size_t heightPos = resStr.find("\"height\"");
                    if (heightPos != std::string::npos) {
                        std::size_t heightColon = resStr.find(':', heightPos);
                        std::size_t heightIndex = heightColon + 1;
                        double h = 0;
                        if (!JsonHelper::tryExtractJsonNumber(resStr, heightIndex, h, error)) {
                            error.key = "camera.resolution.height";
                            return false;
                        }
                        resHeight = static_cast<int>(h);
                    }
                    hasResolution = true;
                }
            }
        }
    }

    if (!hasResolution) {
        error.message = "camera resolution is required";
        error.key = "camera.resolution";
        return false;
    }

    // validate resolution
    if (resWidth <= 0 || resHeight <= 0) {
        error.message = "resolution width and height must be greater than 0";
        error.key = "camera.resolution";
        return false;
    }

    // extract optional direction
    std::size_t dirPos = cameraObj.find("\"direction\"");
    if (dirPos != std::string::npos) {
        std::size_t dirColon = cameraObj.find(':', dirPos);
        if (dirColon != std::string::npos) {
            std::size_t dirIndex = dirColon + 1;
            dirIndex = JsonHelper::skipWhitespace(cameraObj, dirIndex);
            if (dirIndex < cameraObj.size() && cameraObj[dirIndex] == '{') {
                std::string dirStr;
                if (JsonHelper::tryExtractJsonObject(cameraObj, dirIndex, dirStr, error)) {
                    // parse x
                    std::size_t xPos = dirStr.find("\"x\"");
                    if (xPos != std::string::npos) {
                        std::size_t xColon = dirStr.find(':', xPos);
                        std::size_t xIndex = xColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(dirStr, xIndex, direction.x, error)) {
                            error.key = "camera.direction.x";
                            return false;
                        }
                    }
                    // y
                    std::size_t yPos = dirStr.find("\"y\"");
                    if (yPos != std::string::npos) {
                        std::size_t yColon = dirStr.find(':', yPos);
                        std::size_t yIndex = yColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(dirStr, yIndex, direction.y, error)) {
                            error.key = "camera.direction.y";
                            return false;
                        }
                    }
                    // z
                    std::size_t zPos = dirStr.find("\"z\"");
                    if (zPos != std::string::npos) {
                        std::size_t zColon = dirStr.find(':', zPos);
                        std::size_t zIndex = zColon + 1;
                        if (!JsonHelper::tryExtractJsonNumber(dirStr, zIndex, direction.z, error)) {
                            error.key = "camera.direction.z";
                            return false;
                        }
                    }
                }
            }
        }
    }

    // normalize direction if not zero vector
    if (direction.length() > 0.0) {
        direction.normalize();
    } else {
        direction = Math::Vector3(0.0, 0.0, -1.0); // fallback to default
    }

    // create and assign camera
    camera = Camera(position, direction, fov, resWidth, resHeight);
    return true;
}

    }
}
