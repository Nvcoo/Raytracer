/*
** EPITECH PROJECT, 2026
** JsonHelper
** File description:
** JsonHelper
*/

#include "../../include/parser/JsonHelper.hpp"
#include <cctype>

namespace RayTracer {
namespace Parser {

bool JsonHelper::isWhitespace(char c)
{
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

std::size_t JsonHelper::skipWhitespace(const std::string &content, std::size_t index)
{
    while (index < content.size() && isWhitespace(content[index]))
        ++index;
    return index;
}

bool JsonHelper::tryExtractJsonNumber(const std::string &content, std::size_t &index, double &value, SceneParseError &error)
{
    index = skipWhitespace(content, index);
    if (index >= content.size()) {
        error.message = "unexpected end of input while parsing number";
        return false;
    }

    std::size_t start = index;
    bool hasDecimal = false;
    bool hasExponent = false;

    // handle negative sign
    if (content[index] == '-') {
        ++index;
    }

    // parse digits before decimal
    if (index >= content.size() || !std::isdigit(static_cast<unsigned char>(content[index]))) {
        error.message = "expected digit in number";
        return false;
    }

    while (index < content.size() && std::isdigit(static_cast<unsigned char>(content[index]))) {
        ++index;
    }

    // handle decimal point
    if (index < content.size() && content[index] == '.' && !hasDecimal && !hasExponent) {
        hasDecimal = true;
        ++index;
        if (index >= content.size() || !std::isdigit(static_cast<unsigned char>(content[index]))) {
            error.message = "expected digit after decimal point";
            return false;
        }
        while (index < content.size() && std::isdigit(static_cast<unsigned char>(content[index]))) {
            ++index;
        }
    }

    // handle exponent (e or E)
    if (index < content.size() && (content[index] == 'e' || content[index] == 'E') && !hasExponent) {
        hasExponent = true;
        ++index;
        if (index < content.size() && (content[index] == '+' || content[index] == '-')) {
            ++index;
        }
        if (index >= content.size() || !std::isdigit(static_cast<unsigned char>(content[index]))) {
            error.message = "expected digit in exponent";
            return false;
        }
        while (index < content.size() && std::isdigit(static_cast<unsigned char>(content[index]))) {
            ++index;
        }
    }

    try {
        value = std::stod(content.substr(start, index - start));
        return true;
    } catch (...) {
        error.message = "invalid number format";
        return false;
    }
}

bool JsonHelper::tryExtractJsonString(const std::string &content, std::size_t &index, std::string &value, SceneParseError &error)
{
    index = skipWhitespace(content, index);
    if (index >= content.size() || content[index] != '"') {
        error.message = "expected string value (opening '\"')";
        return false;
    }
    ++index;
    std::string result;
    bool escaping = false;

    while (index < content.size()) {
        const char c = content[index];
        if (escaping) {
            escaping = false;
            result.push_back(c);
            ++index;
            continue;
        }
        if (c == '\\') {
            escaping = true;
            ++index;
            continue;
        }
        if (c == '"') {
            ++index;
            value = result;
            return true;
        }
        result.push_back(c);
        ++index;
    }
    error.message = "unterminated string vlaue";
    return false;
}

bool JsonHelper::tryExtractJsonArray(const std::string &content, std::size_t &index, std::string &arrayStr, SceneParseError &error)
{
    index = skipWhitespace(content, index);
    if (index >= content.size() || content[index] != '[') {
        error.message = "expected json array (opening '[')";
        return false;
    }

    const std::size_t start = index;
    int bracketCount = 0;
    bool inString = false;
    bool escaping = false;

    while (index < content.size()) {
        const char c = content[index];
        if (inString) {
            if (escaping) {
                escaping = false;
                ++index;
                continue;
            }
            if (c == '\\') {
                escaping = true;
                ++index;
                continue;
            }
            if (c == '"')
                inString = false;
            ++index;
            continue;
        }
        if (c == '"') {
            inString = true;
            ++index;
            continue;
        }
        if (c == '[') {
            ++bracketCount;
            ++index;
            continue;
        }
        if (c == ']') {
            --bracketCount;
            ++index;
            if (bracketCount == 0) {
                arrayStr = content.substr(start, index - start);
                return true;
            }
            continue;
        }
        ++index;
    }
    error.message = "untermaed json array";
    return false;
}

bool JsonHelper::nextObjectInArray(const std::string &arrayStr, std::size_t &scanIndex, std::string &objectStr, SceneParseError &error)
{
    scanIndex = skipWhitespace(arrayStr, scanIndex);
    while (scanIndex < arrayStr.size() && (arrayStr[scanIndex] == '[' || arrayStr[scanIndex] == ','))
        ++scanIndex;
    scanIndex = skipWhitespace(arrayStr, scanIndex);

    if (scanIndex >= arrayStr.size() || arrayStr[scanIndex] == ']')
        return false;

    if (arrayStr[scanIndex] != '{') {
        error.message = "array entry must be a json obj";
        return false;
    }
    return tryExtractJsonObject(arrayStr, scanIndex, objectStr, error);
}

bool JsonHelper::tryExtractJsonObject(const std::string &content, std::size_t &index, std::string &objectStr, SceneParseError &error)
{
    index = skipWhitespace(content, index);
    if (index >= content.size() || content[index] != '{') {
        error.message = "expected json obj (opening '{')";
        return false;
    }

    std::size_t start = index;
    int braceCount = 0;
    bool inString = false;
    bool escaping = false;

    while (index < content.size()) {
        const char c = content[index];

        if (inString) {
            if (escaping) {
                escaping = false;
                ++index;
                continue;
            }
            if (c == '\\') {
                escaping = true;
                ++index;
                continue;
            }
            if (c == '"') {
                inString = false;
            }
            ++index;
            continue;
        }

        if (c == '"') {
            inString = true;
            ++index;
            continue;
        }

        if (c == '{') {
            ++braceCount;
            ++index;
            continue;
        }

        if (c == '}') {
            --braceCount;
            ++index;
            if (braceCount == 0) {
                objectStr = content.substr(start, index - start);
                return true;
            }
            continue;
        }

        ++index;
    }

    error.message = "unterminated json obj";
    return false;
}

bool JsonHelper::tryExtractJsonBool(const std::string &content, std::size_t &index, bool &value, SceneParseError &error)
{
    index = skipWhitespace(content, index);
    if (index >= content.size()) {
        error.message = "unexpected end of input while parsing bool";
        return false;
    }
    if (index + 4 <= content.size() && content.substr(index, 4) == "true") {
        value = true;
        index += 4;
        return true;
    }
    if (index + 5 <= content.size() && content.substr(index, 5) == "false") {
        value = false;
        index += 5;
        return true;
    }
    error.message = "expected 'true' or 'false' for plane";
    return false;
}

    }
}
