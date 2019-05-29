//  PROI project 3
//  Marcin Białek


#include <Identifiable.h>



std::atomic<uintmax_t> Identifiable::nextId(0);



auto Identifiable::getId() const -> uintmax_t {
    return id;
}



bool Identifiable::operator==(Identifiable &other) const {
    return id == other.id;
}



