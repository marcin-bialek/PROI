//  PROI project 3
//  Marcin Białek


#include <Random.h>



std::random_device Random::device;
std::default_random_engine Random::engine(device());



auto Random::number() -> uintmax_t {
    return engine();
}



auto Random::numberFromRange(uintmax_t from, uintmax_t to) -> uintmax_t {
    std::uniform_int_distribution<uintmax_t> dist(from, to);
    return dist(engine);
}



auto Random::fraction() -> double {
    return (double)number() / (double)UINTMAX_MAX;
}



bool Random::trueWithProbabilityOf(double p) {
    std::bernoulli_distribution dist(p);
    return dist(engine);
}

