//  PROI project 3
//  Marcin Białek


#pragma once
#include <atomic>



class Identifiable {
    static std::atomic<uintmax_t> nextId;
    const uintmax_t id;
    
    
public:
    Identifiable(): id(nextId++) {}
    virtual ~Identifiable() = default;
    
    auto getId() const -> uintmax_t;
    bool operator==(Identifiable &other) const;
};

