//  PROI project 3
//  Marcin Białek


#pragma once
#include <Exception.h>
#include <Json.h>

#include <memory>
#include <string>


class JsonParser {
public:
    struct {
        uintmax_t position = 0;
        uintmax_t line = 1;
        std::string text;
    } context;
    
    
    char currentChar();
    void next();
    void previous();
    bool test(std::string value);
    void skipWhitespaces();
    
    
    auto parseValue() -> std::shared_ptr<Json::Value>;
    auto parseString() -> std::shared_ptr<Json::String>;
    auto parseInteger() -> std::shared_ptr<Json::Value>;
    auto parseFraction(int intPart) -> std::shared_ptr<Json::Double>;
    auto parseObject() -> std::shared_ptr<Json::Object>;
    auto parseArray() -> std::shared_ptr<Json::Array>;
    
    
public:
    JsonParser() {}
    void parse(std::string text, Json &json);
    
    
    
    struct ParserError: public Exception {
        ParserError(std::string message, uintmax_t line): Exception("Parser error: " + message + " (line " + std::to_string(line) + ")") {}
    };
    
    
    struct Invalid final: public ParserError {
        Invalid(std::string identifier, uintmax_t line): ParserError("invalid " + identifier, line) {}
    };
    
    
    struct Expected final: public ParserError {
        Expected(std::string identifier, uintmax_t line): ParserError("expected " + identifier, line) {}
    };
    
    
    struct Unexpected final: public ParserError {
        Unexpected(std::string identifier, uintmax_t line): ParserError("unexpected " + identifier, line) {}
    };
};

