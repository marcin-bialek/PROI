//  PROI project 3
//  Marcin Białek


#pragma once
#include <Identifiable.h>
#include <Medicine.h>

#include <map>
#include <string>



struct Product {
    std::string name;
    std::string group;
    double price;
    double tax;
    
    bool operator<(const Product &other) const;
};



class Bill: public Identifiable {
protected:
    std::map<Product, size_t> products;
    double totalPrice = 0;
    
public:
    Bill() {}
    virtual ~Bill() = default;
    virtual auto toString() const -> std::string = 0;
    auto sum() -> double;
};



struct Receipt: public Bill {
    void addProduct(std::string name, double price);
    auto toString() const -> std::string;
};



struct Invoice: public Bill {
    std::string nip;
    void addProduct(std::string name, std::string group, double price, double tax);
    auto toString() const -> std::string;
};
