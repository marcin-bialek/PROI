//  PROI project 3
//  Marcin Białek


#pragma once
#include <random>



class Random {
    static std::random_device device;
    static std::default_random_engine engine;
    
    
public:
    static auto number() -> uintmax_t;
    static auto numberFromRange(uintmax_t from, uintmax_t to) -> uintmax_t;
    static auto fraction() -> double;
    static bool trueWithProbabilityOf(double p);
};



