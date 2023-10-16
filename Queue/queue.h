#ifndef QUEUE_H
#define QUEUE_H
#include "../DLinkedList/dLinkedList.h"
#include <stdexcept>
template<class T>
class Queue {
protected:
    DLinkedList<T> list;
public:
    Queue();
    void push(T item);
    T pop();
    T top();
    bool empty();
    int size();
    void clear();
    std::string toString();
};

template <class T>
Queue<T>::Queue() {
    
}

template <class T>
std::string Queue<T>::toString() {
    return this->list.toString();
}

// Push new element into the end of the queue
template <class T>
void Queue<T>::push(T item) {
    int size = this->list.size();
    this->list.add(size, item);
}

// Remove an element in the head of the queue
template <class T>
T Queue<T>::pop() noexcept(false) {
    return this->list.removeAt(0);
}

// Get value of the element in the head of the queue
template <class T>
T Queue<T>::top() {
    return this->list.get(0);
}

// Determine if the queue is empty
template <class T>
bool Queue<T>::empty() {
    return this->list.size() <= 0;
}

// Get the size of the queue
template <class T>
int Queue<T>::size() {
    return this->list.size();
}

// Clear all elements of the queue
template <class T>
void Queue<T>::clear() {
    this->list.clear();
}



#endif // QUEUE_H