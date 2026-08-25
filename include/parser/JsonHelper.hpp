/*
** EPITECH PROJECT, 2026
** JsonHelper
** File description:
** JsonHelper
*/
#pragma once

#include <cstddef>
#include <string>
#include "../SceneParser.hpp"

namespace RayTracer {
namespace Parser {

class JsonHelper {
public:
    static bool tryExtractJsonNumber(const std::string &content, std::size_t &index, double &value, SceneParseError &error);
    static bool tryExtractJsonObject(const std::string &content, std::size_t &index, std::string &objectStr, SceneParseError &error);
    static bool tryExtractJsonArray(const std::string &content, std::size_t &index, std::string &arrayStr, SceneParseError &error);
    static bool tryExtractJsonBool(const std::string &content, std::size_t &index, bool &value, SceneParseError &error);
    static bool tryExtractJsonString(const std::string &content, std::size_t &index, std::string &value, SceneParseError &error);
    static bool nextObjectInArray(const std::string &arrayStr, std::size_t &scanIndex, std::string &objectStr, SceneParseError &error);
    static std::size_t skipWhitespace(const std::string &content, std::size_t index);

private:
    static bool isWhitespace(char c);
};

    }
}
