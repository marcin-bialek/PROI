//  PROI project 3
//  Marcin Białek


#include <Json.h>
#include <Json.h>
#include <JsonParser.h>
#include <Exception.h>

#include <fstream>
#include <sstream>



Json::Value::operator std::string() const {
    if(auto object = dynamic_cast<const String*>(this)) {
        return object->getValue();
    }
    
    throw InvalidCasting("string");
}



Json::Value::operator int() const {
    if(auto object = dynamic_cast<const Integer*>(this)) {
        return object->getValue();
    }
    
    throw InvalidCasting("int");
}



Json::Value::operator double() const {
    if(auto object = dynamic_cast<const Double*>(this)) {
        return object->getValue();
    }
    
    throw InvalidCasting("double");
}



Json::Value::operator bool() const {
    if(auto object = dynamic_cast<const Bool*>(this)) {
        return object->getValue();
    }
    
    throw InvalidCasting("bool");
}



auto Json::String::getValue() const -> const std::string& {
    return value;
}



auto Json::String::length() const -> size_t {
    return value.length();
}



auto Json::Integer::getValue() const -> int {
    return value;
}



auto Json::Integer::length() const -> size_t {
    return 1;
}



auto Json::Double::getValue() const -> double {
    return value;
}



auto Json::Double::length() const -> size_t {
    return 1;
}



void Json::Object::set(std::string key, std::shared_ptr<Value> value) {
    values[key] = value;
}



auto Json::Object::length() const -> size_t {
    return values.size();
}



auto Json::Object::getValue(std::string key) const -> std::shared_ptr<Json::Value> {
    if(values.find(key) == values.end())
        return nullptr;
    
    return values.at(key);
}



void Json::Object::forEach(std::function<void (std::string, Value&)> callback) const {
    for(auto i = values.begin(); i != values.end(); i++) {
        callback(i->first, *i->second.get());
    }
}



void Json::Array::append(std::shared_ptr<Value> value) {
    values.push_back(value);
}



auto Json::Array::length() const -> size_t {
    return values.size();
}



auto Json::Array::getValue(uintmax_t index) const -> std::shared_ptr<Json::Value> {
    if(index > values.size())
        return nullptr;
    
    return values[index];
}



void Json::Array::forEach(std::function<void (std::string, Value&)> callback) const {
    for(uintmax_t i = 0; i < values.size(); i++) {
        callback(std::to_string(i), *values[i]);
    }
}



auto Json::stringToIndex(std::string str) const -> uintmax_t {
    uintmax_t index = 0;
    
    for(const char c : str) {
        if(isnumber(c)) {
            index = index * 10 + c - '0';
        }
        
        else {
            throw JsonError("key \"" + str + "\" must be a number (object is an array)");
        }
    }
    
    return index;
}



void Json::loadFromFile(std::string path) {
    std::fstream file;
    file.open(path, std::ios::in);
    
    if(!file.good()) {
        throw JsonError("error opening json file");
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    JsonParser parser;
    parser.parse(buffer.str(), *this);
}



void Json::setRoot(Object &object) {
    root = object;
}



auto Json::getObject(Value *object, std::string &key, std::string &path) const -> Value* {
    if(auto value = dynamic_cast<Object*>(object)) {
        return value->getValue(key).get();
    }
    
    else if(auto value = dynamic_cast<Array*>(object)) {
        auto index = stringToIndex(key);
        return value->getValue(index).get();
    }
    
    else throw JsonError("invalid path \"" + path + "\"");
}



auto Json::operator[](std::string path) const -> const Json::Value& {
    if(path.length() == 0) {
        return root;
    }
    
    if(path[path.length() - 1] != '/') {
        path += '/';
    }
    
    std::string key = "";
    Value *object = const_cast<Object*>(&root);
    
    for(const char c : path) {
        if(c == '/') {
            object = getObject(object, key, path);
            key = "";
        }
        
        else key += c;
    }
    
    if(!object) {
        throw JsonError("invalid path \"" + path + "\"");
    }
        
    return *object;
}

