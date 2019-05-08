//  PROI project 2
//  Marcin Białek


#pragma once
#include <iostream>
#include <List.h>



template <typename T>
class Multiset {
    
    struct Element {
        T value;
        size_t multiplicity = 1;
        Element(T v, size_t m): value(v), multiplicity(m) {}
        Element(T v): Element(v, 1) {}
    };
    
    List<Element*> elements;
    size_t size = 0;
    
    
    
/**********   Constructors and destructors   **********/

    
public:
    
    Multiset() {}
    
    
    
    Multiset(std::initializer_list<T> elements) {
        for(const T &e : elements) {
            append(e);
        }
    }
    
    
    
    Multiset(std::initializer_list<Element> elements) {
        for(const Element &e : elements) {
            append(e.value, e.multiplicity);
        }
    }
    
    
    
    Multiset(const Multiset<T> &other) {
        *this = other;
    }
    
    
    
    Multiset(Multiset<T> &&other) {
        *this = std::move(other);
    }
    
    
    
    ~Multiset() {
        elements.forEach([](Element *element) {
            delete element;
        });
    }
    

    
/**********   Adding and removing elements   **********/
    
    
    Multiset<T>& append(T value, size_t multiplicity) {
        if(multiplicity != 0) {
            if(Element *e = findElementWithValueOf(value)) {
                e->multiplicity += multiplicity;
            }
            else {
                elements.append(new Element(value, multiplicity));
            }
            
            size += multiplicity;
        }
        
        return *this;
    }
    
    
    
    Multiset<T>& append(T value) {
        return append(value, 1);
    }
    
    
    
    Multiset<T>& remove(const T &value) {
        if(Element *element = findElementWithValueOf(value)) {
            element->multiplicity--;
            size--;
            
            if(element->multiplicity == 0) {
                delete element;
                elements.remove(element);
            }
        }
        
        return *this;
    }
    
    
    
    Multiset<T>& removeAll(const T &value) {
        if(Element *element = findElementWithValueOf(value)) {
            size -= element->multiplicity;
            delete element;
            elements.remove(element);
        }
        
        return *this;
    }
    
    
    
/**********   Iterating through all elements   **********/
    

private:
    
    void forEach(std::function<void (Element&)> callback) const {
        elements.forEach([&callback](Element *e) { callback(*e); });
    }
    
    
public:
    
    void forEach(std::function<void (T&)> callback) const {
        elements.forEach([&callback](Element *e) { callback(e->value); });
    }
    
    
    
/**********   Finding elements   **********/
    
    
private:
    
    Element* findElementWithValueOf(T value) const {
        Element *element = nullptr;
        
        elements.some([&value, &element](Element *e) {
            if(e->value == value) {
                element = e;
                return true;
            }
            
            return false;
        });
        
        return element;
    }
    
    
    
/**********   Info about the set   **********/
    
    
public:
    
    size_t multiplicityOf(const T &value) const {
        if(Element *element = findElementWithValueOf(value)) {
            return element->multiplicity;
        }
        
        return 0;
    }
    
    
    
    bool doesExist(const T &value) const {
        return findElementWithValueOf(value);
    }
    
    
    
    size_t length() const {
        return size;
    }
    
    
    
/**********   Operations on sets   **********/
    
    
    
    Multiset<T> sum(const Multiset<T> &adden) const {
        Multiset<T> result = *this;
        
        adden.forEach([&result](Element &a) {
            result.append(a.value, a.multiplicity);
        });
        
        return result;
    }
    
    
    
    Multiset<T> intersection(const Multiset<T> &factor) const {
        Multiset<T> product;
        
        factor.forEach([this, &product](Element &a) {
            if(Element *b = findElementWithValueOf(a.value)) {
                product.append(a.value, std::min(a.multiplicity, b->multiplicity));
            }
        });
        
        return product;
    }
    
    
    
/**********   Operators   **********/
    
    
    Multiset<T>& operator=(const Multiset<T> &other) {
        if(this != &other) {
            other.elements.forEach([this](Element *element) {
                append(element->value, element->multiplicity);
            });
        }
        
        return *this;
    }
    
    
    
    Multiset<T>& operator=(Multiset<T> &&other) {
        if(this != &other) {
            size = other.size;
            elements = std::move(other.elements);
            
            other.size = 0;
        }
        
        return *this;
    }
    
    
    
    friend Multiset<T> operator+(const Multiset<T> &A, Multiset<T> B) {
        return A.sum(B);
    }
    
    
    
    friend Multiset<T> operator*(const Multiset<T> &A, Multiset<T> B) {
        return A.intersection(B);
    }
    
    
    
    friend bool operator==(const Multiset<T> &A, const Multiset<T> &B) {
        return A.length() == A.intersection(B).length();
    }
    
    
    
    friend bool operator!=(const Multiset<T> &A, const Multiset<T> &B) {
        return !(A == B);
    }
    
    
    
    friend std::ostream& operator<<(std::ostream &stream, const Multiset<T> &A) {
        stream << "{";
        
        A.elements.forEach([&stream](Element *e, bool isLast) {
            stream << "{ " << e->value << ", " << e->multiplicity << " }" << (isLast ? "" : ", ");
        });
        
        return stream << "}";
    }
    
};
