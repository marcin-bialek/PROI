//  PROI project 3
//  Marcin Białek


#include <JsonParser.h>

#include <cmath>



char JsonParser::currentChar() {
    if(context.position >= context.text.length()) {
        return '\0';
    }
    
    return context.text[context.position];
}



void JsonParser::next() {
    if(currentChar() == '\n') {
        context.line++;
    }
    
    context.position++;
}



void JsonParser::previous() {
    context.position--;
    
    if(currentChar() == '\n') {
        context.line--;
    }
}



bool JsonParser::test(std::string value) {
    for(uintmax_t i = 0; i < value.length(); i++) {
        if(currentChar() != value[i]) {
            while(i--) {
                previous();
            }
            
            return false;
        }
        
        next();
    }
    
    return true;
}



void JsonParser::skipWhitespaces() {
    while(iswspace(currentChar())) {
        next();
    }
}



auto JsonParser::parseValue() -> std::shared_ptr<Json::Value> {
    if(currentChar() == '"')
        return parseString();
    else if(isnumber(currentChar()) || currentChar() == '-')
        return parseInteger();
    else if(currentChar() == '{')
        return parseObject();
    else if(currentChar() == '[')
        return parseArray();
    else if(test("true"))
        return std::make_shared<Json::Bool>(true);
    else if(test("false"))
        return std::make_shared<Json::Bool>(false);
    else if(test("null"))
        throw ParserError("Null values are not supported.", context.line);
                        
    throw Invalid("value", context.line);
}



auto JsonParser::parseString() -> std::shared_ptr<Json::String> {
    if(test("\"")) {
        std::string value = "";
        
        while(!test("\"")) {
            if(currentChar() == '\0') {
                throw Unexpected("end of string", context.line);
            }
                
            value += currentChar();
            next();
        }
        
        return std::make_shared<Json::String>(value);
    }
    
    throw Invalid("string", context.line);
}



auto JsonParser::parseInteger() -> std::shared_ptr<Json::Value> {
    int value = 0;
    int mul = 1;
    
    if(test("-")) {
        mul = -1;
    }
    
    while(isnumber(currentChar())) {
        value = value * 10 + currentChar() - '0';
        next();
    }
    
    if(test(".")) {
        return parseFraction(value * mul);
    }
    
    return std::make_shared<Json::Integer>(value * mul);
}



auto JsonParser::parseFraction(int intPart) -> std::shared_ptr<Json::Double> {
    double value = intPart;
    
    for(uintmax_t decimalPlaces = 1; isnumber(currentChar()); decimalPlaces++) {
        value += (currentChar() - '0') / pow(10, decimalPlaces);
        next();
    }
    
    return std::make_shared<Json::Double>(value);
}



auto JsonParser::parseObject() -> std::shared_ptr<Json::Object> {
    if(!test("{"))
        throw Expected("{", context.line);
        
        skipWhitespaces();
        auto object = std::make_shared<Json::Object>();
        
        while(currentChar() == '"') {
            auto key = parseString()->getValue();
            skipWhitespaces();
            
            if(!test(":")) {
                throw Expected(":", context.line);
            }
                
            skipWhitespaces();
            object->set(key, parseValue());
            skipWhitespaces();
            
            if(!test(",")) {
                break;
            }
            
            skipWhitespaces();
        }
    
    if(!test("}")) {
        throw Expected("}", context.line);
    }
        
    return object;
}



auto JsonParser::parseArray() -> std::shared_ptr<Json::Array> {
    if(!test("["))
        throw Expected("[", context.line);
        
        skipWhitespaces();
        auto array = std::make_shared<Json::Array>();
        
        while(!test("]")) {
            array->append(parseValue());
            skipWhitespaces();
            
            if(!test(",")) {
                break;
            }
            
            skipWhitespaces();
        }
    
    if(!test("]")) {
        throw Expected("]", context.line);
    }
    
    return array;
}



void JsonParser::parse(std::string text, Json &json) {
    context.text = text;
    json.setRoot(*parseObject());
}

