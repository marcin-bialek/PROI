//  PROI project 1
//  Marcin Białek


#include <IntegerQueue.h>


IntegerQueue::~IntegerQueue() {
    for(QueueNode *node = front, *previous = nullptr; node; node = previous) {
        previous = node->previous;
        delete node;
    }
}



size_t IntegerQueue::length() const {
    return size;
}



size_t IntegerQueue::maxLength() const {
    return capacity;
}



bool IntegerQueue::isFull() const {
    return size == capacity;
}



bool IntegerQueue::isEmpty() const {
    return size == 0;
}



void IntegerQueue::enqueue(int value) {
    if(isFull()) return;
    
    auto node = new QueueNode(value);
    
    if(isEmpty()) {
        front = back = node;
    }
    else {
        back->previous = node;
        back = node;
    }
    
    size++;
}



void IntegerQueue::enqueue(std::initializer_list<int> values) {
    for(int value : values) {
        enqueue(value);
    }
}



void IntegerQueue::enqueueOverride(int value) {
    if(isFull()) {
        back->value = value;
        return;
    }
    
    enqueue(value);
}



void IntegerQueue::enqueueOverride(std::initializer_list<int> values) {
    for(int value : values) {
        enqueueOverride(value);
    }
}



int IntegerQueue::dequeue() {
    if(isEmpty()) {
        return 0;
    }
    
    auto node = front;
    int value = front->value;
    front = front->previous;
    delete node;
    
    size--;
    return value;
}



void IntegerQueue::forEach(std::function<void (int, bool)> function) const {
    for(auto node = front; node; node = node->previous) {
        function(node->value, !node->previous);
    }
}



void IntegerQueue::forEach(std::function<void (int)> function) const {
    forEach([function](int value, bool last) { (void)last; function(value); });
}



void operator+=(IntegerQueue &left, const IntegerQueue &right) {
    left.capacity += right.capacity;

    right.forEach([&left](int value) {
        left.enqueue(value);
    });
}



IntegerQueue& operator+(const IntegerQueue& left, const IntegerQueue& right) {
    auto queue = new IntegerQueue(left.capacity + right.capacity);
    *queue += left;
    *queue += right;
    return *queue;
}



bool operator==(const IntegerQueue& left, const IntegerQueue& right) {
    if(left.size != right.size) {
        return false;
    }
    
    for(auto a = left.front, b = right.front; a && b; a = a->previous, b = b->previous) {
        if(a->value != b->value) {
            return false;
        }
    }
    
    return true;
}



bool operator!=(const IntegerQueue& left, const IntegerQueue& right) {
    return !(left == right);
}



std::ostream& operator<<(std::ostream &stream, const IntegerQueue &queue) {
    stream << "[ ";
    
    queue.forEach([&stream](int value, bool last) {
        stream << value << (last ? " " : ", ");
    });
    
    return stream << "]";
}

