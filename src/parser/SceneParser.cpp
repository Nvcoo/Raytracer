/*
** EPITECH PROJECT, 2026
** SceneParser
** File description:
** SceneParser
*/

#include "../../include/SceneParser.hpp"
#include "../../include/parser/CameraParser.hpp"
#include "../../include/parser/LightsParser.hpp"
#include "../../include/parser/PrimitivesParser.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

namespace RayTracer {

namespace {

struct Cursor {
    std::size_t line = 1;
    std::size_t column = 1;
};

bool is_whitespace(char c)
{
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

std::size_t skip_whitespace(const std::string &content, std::size_t index)
{
    while (index < content.size() && is_whitespace(content[index]))
        ++index;
    return index;
}

}

std::string SceneParseError::toString() const
{
    std::ostringstream stream;

    stream << "scene parse error at line " << line << ", column " << column;
    if (!key.empty())
        stream << " near key '" << key << "'";
    stream << ": " << message;
    return stream.str();
}

SceneParseResult SceneParser::parseFile(const std::string &path)
{
    std::ifstream input(path);
    SceneParseResult result;

    if (!input.is_open()) {
        result.ok = false;
        result.error.message = "unable to open scene file: " + path;
        return result;
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    return parseText(buffer.str());
}

SceneParseResult SceneParser::parseText(const std::string &content)
{
    SceneParseResult result;
    result.ok = false;

    if (content.empty()) {
        result.error.message = "empty scene file";
        return result;
    }

    const std::size_t first = skip_whitespace(content, 0);
    if (first >= content.size() || content[first] != '{') {
        result.error.line = 1;
        result.error.column = 1;
        result.error.message = "root scene value must be a json object";
        return result;
    }

    std::vector<char> delimiterStack;
    delimiterStack.reserve(32);

    Cursor cursor;
    bool inString = false;
    bool escaping = false;
    bool readingString = false;
    std::string token;
    std::string lastKey;
    std::size_t objectDepth = 0;
    std::size_t arrayDepth = 0;

    for (std::size_t i = 0; i < content.size(); ++i) {
        const char c = content[i];

        if (c == '\n') {
            ++cursor.line;
            cursor.column = 1;
        } else {
            ++cursor.column;
        }

        if (inString) {
            if (escaping) {
                escaping = false;
                continue;
            }
            if (c == '\\') {
                escaping = true;
                continue;
            }
            if (c == '"') {
                inString = false;
                readingString = false;

                const std::size_t next = skip_whitespace(content, i + 1);
                if (next < content.size() && content[next] == ':') {
                    lastKey = token;
                    if (objectDepth == 1 && arrayDepth == 0)
                        result.scene.topLevelKeys.push_back(token);
                }
                token.clear();
                continue;
            }
            if (readingString)
                token.push_back(c);
            continue;
        }

        if (c == '"') {
            inString = true;
            readingString = true;
            token.clear();
            continue;
        }

        if (is_whitespace(c))
            continue;

        if (c == '{') {
            delimiterStack.push_back('{');
            ++objectDepth;
            continue;
        }
        if (c == '[') {
            delimiterStack.push_back('[');
            ++arrayDepth;
            continue;
        }
        if (c == '}') {
            if (delimiterStack.empty() || delimiterStack.back() != '{') {
                result.error.line = cursor.line;
                result.error.column = cursor.column;
                result.error.key = lastKey;
                result.error.message = "unexpected closing '}'";
                return result;
            }
            delimiterStack.pop_back();
            if (objectDepth > 0)
                --objectDepth;
            continue;
        }
        if (c == ']') {
            if (delimiterStack.empty() || delimiterStack.back() != '[') {
                result.error.line = cursor.line;
                result.error.column = cursor.column;
                result.error.key = lastKey;
                result.error.message = "unexpected closing ']'";
                return result;
            }
            delimiterStack.pop_back();
            if (arrayDepth > 0)
                --arrayDepth;
            continue;
        }
    }

    if (inString) {
        result.error.line = cursor.line;
        result.error.column = cursor.column;
        result.error.key = lastKey;
        result.error.message = "unterminated string literal";
        return result;
    }

    if (!delimiterStack.empty()) {
        result.error.line = cursor.line;
        result.error.column = cursor.column;
        result.error.key = lastKey;
        result.error.message = "unclosed json delimiter";
        return result;
    }

    result.ok = true;
    result.scene.rawContent = content;

    // parse camera block if present
    if (std::find(result.scene.topLevelKeys.begin(), result.scene.topLevelKeys.end(), "camera") != 
        result.scene.topLevelKeys.end()) {
        if (!Parser::CameraParser::tryParseCamera(content, result.scene.camera, result.error)) {
            result.ok = false;
            return result;
        }
    }

    // parse lights block if present
    if (std::find(result.scene.topLevelKeys.begin(), result.scene.topLevelKeys.end(), "lights") !=
        result.scene.topLevelKeys.end()) {
        if (!Parser::LightsParser::tryParseLights(content, result.scene, result.error)) {
            result.ok = false;
            return result;
        }
    }

    // parse primitives block if present
    if (std::find(result.scene.topLevelKeys.begin(), result.scene.topLevelKeys.end(), "primitives") !=
        result.scene.topLevelKeys.end()) {
        if (!Parser::PrimitivesParser::tryParsePrimitives(content, result.scene, result.error)) {
            result.ok = false;
            return result;
        }
    }

    return result;
}

}
