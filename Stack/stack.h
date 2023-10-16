#ifndef STACK_H
#define STACK_H
#include "../DLinkedList/dLinkedList.h"
#include <stdexcept>
template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack();
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
    std::string toString();
};

template <class T>
Stack<T>::Stack() {

}

template <class T>
std::string Stack<T>::toString() {
    return this->list.toString();
}

// Push new element into the top of the stack
template <class T>
void Stack<T>::push(T item) {
    int size = this->list.size();
    this->list.add(size, item);
}

// Remove an element on top of the stack
template <class T>
T Stack<T>::pop() {
    int size = this->list.size();
    if (size <= 0)
        throw new std::out_of_range("No element to pop");
    return this->list.removeAt(size - 1);
}

// Get value of the element on top of the stack
template <class T>
T Stack<T>::top() {
    int size = this->list.size();
    if (size <= 0)
        throw new std::out_of_range("No element to get");
    return this->list.get(size - 1);
}

// Determine if the stack is empty
template <class T>
bool Stack<T>::empty() {
    return this->list.size() == 0;
}

// Get the size of the stack
template <class T>
int Stack<T>::size() {
    return this->list.size();
}

// Clear all elements of the stack
template <class T>
void Stack<T>::clear() {
    this->list.clear();
}

#endif