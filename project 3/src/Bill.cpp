//  PROI project 3
//  Marcin Białek


#include <Constants.h>
#include <Bill.h>

#include <iomanip>
#include <sstream>



auto Bill::sum() -> double {
    return totalPrice;
}



bool Product::operator<(const Product &other) const {
    return name < other.name;
}


void Receipt::addProduct(std::string name, double price) {
    Product product = { name, "", price, 0 };
    
    if(products.find(product) == products.end()) {
        products[product] = 1;
    }
    else {
        products[product] = products[product] + 1;
    }
    
    totalPrice += price;
}



auto Receipt::toString() const -> std::string {
    std::stringstream ss;
    
    for(auto &product : products) {
        ss << RECEIPT_FORMAT_A(product.first.name, product.second, product.first.price * product.second);
    }
    
    ss << RECEIPT_FORMAT_B(totalPrice);
    return ss.str();
}
        
        
        
void Invoice::addProduct(std::string name, std::string group, double price, double tax) {
    Product product = { name, group, price, tax };
    
    if(products.find(product) == products.end()) {
        products[product] = 1;
    }
    else {
        products[product] = products[product] + 1;
    }
    
    totalPrice += price;
}



auto Invoice::toString() const -> std::string {
    std::stringstream ss;
    ss << INVOICE_FORMAT_A(nip);
    ss << INVOICE_FORMAT_B;
    
    double totalNetto = 0;
    size_t totalCount = 0;
    
    for(auto &product : products) {
        totalCount += product.second;
        double netto = product.first.price / (1 + product.first.tax) * product.second;
        totalNetto += netto;
        ss << INVOICE_FORMAT_C(product.first.name, product.second, product.first.tax, netto, product.first.price * product.second, product.first.group);
    }
    
    ss << INVOICE_FORMAT_D(totalCount, totalNetto, totalPrice);
    return ss.str();
}
