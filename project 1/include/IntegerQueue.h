//  PROI project 1
//  Marcin Białek


#pragma once
#include <cstddef>
#include <functional>
#include <iostream>


// Implementation of FIFO queue of integers.
class IntegerQueue {
    
    struct QueueNode {
        int value;
        QueueNode *previous = nullptr;
        QueueNode(int v): value(v) {}
    };
    
    QueueNode *front = nullptr;
    QueueNode *back = nullptr;
    size_t size = 0;
    size_t capacity;
    
public:
    IntegerQueue(size_t c): capacity(c) {}
    IntegerQueue(): capacity(SIZE_MAX) {}
    ~IntegerQueue();
    
    size_t length() const;
    size_t maxLength() const;
    bool isFull() const;
    bool isEmpty() const;
    
    void enqueue(int);
    void enqueue(std::initializer_list<int>);
    void enqueueOverride(int);
    void enqueueOverride(std::initializer_list<int>);
    int dequeue();
    
    void forEach(std::function<void (int, bool)>) const;
    void forEach(std::function<void (int)>) const;

    friend void operator+=(IntegerQueue&, const IntegerQueue&);
    friend IntegerQueue& operator+(const IntegerQueue&, const IntegerQueue&);
    friend bool operator==(const IntegerQueue&, const IntegerQueue&);
    friend bool operator!=(const IntegerQueue&, const IntegerQueue&);
    friend std::ostream& operator<<(std::ostream&, const IntegerQueue&);
};
