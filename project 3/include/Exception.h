//  PROI project 3
//  Marcin Białek


#pragma once
#include <string>


extern volatile bool end;


class Exception {
    const std::string message;
    
    
public:
    Exception(std::string message): message(message) {}
    virtual ~Exception() = default;
    
    auto getMessage() const -> const std::string&;
};
