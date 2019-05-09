//  PROI project 2
//  Marcin Białek


#pragma once
#include <iostream>
#include <functional>



template <typename T>
class List {

    struct Node {
        T value;
        Node *next = nullptr;
        Node(T v, Node *n): value(v), next(n) {}
    } *first = nullptr;
    
    
    
/**********   Constructors and destructors   **********/
 

public:
    
    List() {}
    
    
    
    List(std::initializer_list<T> elements) {
        for(T e : elements) {
            append(e);
        }
    }
    
    
    
    List(const List<T> &other) {
        *this = other;
    }
    
    
    
    List(List<T> &&other) {
        *this = std::move(other);
    }
    
    
    
    ~List() {
        for(Node *n = first, *next = nullptr; n; n = next) {
            next = n->next;
            delete n;
        }
    }
    
    
    
/**********   Iterating through all elements   **********/

    
    bool some(std::function<bool (T&)> callback) const {
        for(Node *n = first; n; n = n->next) {
            if(callback(n->value)) {
                return true;
            };
        }
        
        return false;
    }
   
    
    
    void forEach(std::function<void (T&, bool)> callback) const {
        for(Node *n = first; n; n = n->next) {
            callback(n->value, !n->next);
        }
    }
    
    
    
    void forEach(std::function<void (T&)> callback) const {
        forEach([&callback](T& v, bool) { callback(v); });
    }
    
    
    
/**********   Adding and removing elements   **********/
    
    
    void append(T element) {
        first = new Node(element, first);
    }
    
    
    
    void remove(T element) {
        for(Node *n = first, *p = nullptr; n; p = n, n = n->next) {
            if(n->value == element) {
                if(p) {
                    p->next = n->next;
                }
                else {
                    first = n->next;
                }
                
                delete n;
                return;
            }
        }
    }
    
    
    
/**********   Operators   **********/
    
    
    List<T>& operator=(const List<T> &other) {
        if(this != &other) {
            other.forEach([this](T &e) {
                append(e);
            });
        }
        
        return *this;
    }
    
    
    
    List<T>& operator=(List<T> &&other) {
        if(this != &other) {
            first = other.first;
            other.first = nullptr;
        }
        
        return *this;
    }
    
};

