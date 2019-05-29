//  PROI project 3
//  Marcin Białek


#pragma once
#include <Exception.h>

#include <map>
#include <memory>
#include <string>
#include <vector>



class Json {
public:
    struct Value {
        virtual ~Value() = default;
        virtual auto length() const -> size_t = 0;
        virtual void forEach(std::function<void (std::string, Value&)>) const = 0;
        
        operator std::string() const;
        operator int() const;
        operator double() const;
        operator bool() const;
    };
    
    
    
    class String final: public Value {
        std::string value;
        
    public:
        String(std::string value): value(value) {}
        auto getValue() const -> const std::string&;
        auto length() const -> size_t;
        void forEach(std::function<void (std::string, Value&)>) const {}
    };
    
    
    
    class Integer final: public Value {
        int value;
        
    public:
        Integer(int value): value(value) {}
        auto getValue() const -> int;
        auto length() const -> size_t;
        void forEach(std::function<void (std::string, Value&)>) const {}
    };
    
    
    
    class Double final: public Value {
        double value;
        
    public:
        Double(double value): value(value) {}
        auto getValue() const -> double;
        auto length() const -> size_t;
        void forEach(std::function<void (std::string, Value&)>) const {}
    };
    
    
    
    class Object final: public Value {
        std::map<std::string, std::shared_ptr<Value>> values;
        
    public:
        Object() {};
        void set(std::string key, std::shared_ptr<Value> value);
        auto getValue(std::string key) const -> std::shared_ptr<Json::Value>;
        auto length() const -> size_t;
        void forEach(std::function<void (std::string, Value&)>) const;
    };
    
    
    
    class Array final: public Value {
        std::vector<std::shared_ptr<Value>> values;
        
    public:
        Array() {}
        void append(std::shared_ptr<Value> value);
        auto getValue(uintmax_t index) const -> std::shared_ptr<Json::Value>;
        auto length() const -> size_t;
        void forEach(std::function<void (std::string, Value&)>) const;
    };
    
    
    
    class Bool final: public Value {
        bool value;
        
    public:
        Bool(bool value): value(value) {}
        bool getValue() const { return value; }
        auto length() const -> size_t { return 1; }
        void forEach(std::function<void (std::string, Value&)>) const {}
    };
    
    
private:
    Object root;
    
    auto stringToIndex(std::string) const -> uintmax_t;
    auto getObject(Value *object, std::string &key, std::string &path) const -> Value*;
    
    
public:
    void loadFromFile(std::string path);
    void setRoot(Object &object);
    
    auto operator[](std::string path) const -> const Value&;
    
    
    
    struct JsonError: public Exception {
        JsonError(std::string message): Exception("JSON error: " + message) {}
    };
    
    
    struct InvalidCasting final: public JsonError {
        InvalidCasting(std::string to): JsonError("requested value is not of type " + to) {}
    };
};
