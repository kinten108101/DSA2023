#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include "../Utils/utils.h"

using namespace std;

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList() {};
    std::string toString();
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };

};

template <class T>
DLinkedList<T>::DLinkedList(): head(nullptr), tail(nullptr), count(0) {}

template <class T>
string DLinkedList<T>::toString() {
    string str("");
    str += "[";
    Node *ptr = this->head;
    for (int i = 0; i < this->count; i++) {
        if (i == 0) str += to_string(ptr->data);
        else str += "," + to_string(ptr->data);
        ptr = ptr->next;
    }
    str += "]";
    return str;
}

/* Insert an element into the end of the list. */
template <class T>
void DLinkedList<T>::add(const T& e) {
    Node *node = new Node(e);
    if (this->count <= 0) {
        this->head = this->tail = node;
        node->next = node->previous = nullptr;
    } else {
        this->tail->next = node;
        node->next = nullptr;
        node->previous = this->tail;
        this->tail = node;
    }
    this->count++;
}

/* Insert an element into the list at given index. */ 
template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    int idx = index;
    Node *node = new Node(e);
    Node *ptr = this->head;
    Node *previous = NULL;

    while (idx--) {
        previous = ptr;
        ptr = ptr->next;
    }

    if (previous != NULL) previous->next = node;
    node->previous = previous;
    node->next = ptr;
    if (ptr != NULL) ptr->previous = node;

    if (index <= 0) this->head = node;
    if (index >= this->count) this->tail = node;
    this->count++;
}

/* Return the length (size) of list */ 
template<class T>
int DLinkedList<T>::size() {
    return this->count;
}

/* Give the data of the element at given index in the list. */
template<class T>
T DLinkedList<T>::get(int index) {
    if (index <= 0) return this->head->data;
    else if (index >= this->count - 1) return this->tail->data;
    int idx = index;
    Node *ptr = this->head;
    while (idx--)
        ptr = ptr->next;
    return ptr->data;
}

/* Assign new value for element at given index in the list */
template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    if (index <= 0) {
        this->head->data = e;
    } else if (index >= this->count - 1) {
        this->tail->data = e;
    } else {
        int idx = index;
        Node *ptr = this->head;
        while (idx--)
            ptr = ptr->next;   
        ptr->data = e;
    }
}

/* Check if the list is empty or not. */
template<class T>
bool DLinkedList<T>::empty() {
    return this->count <= 0;    
}

/* Return the first index wheter item appears in list, otherwise return -1 */
template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    int idx = 0;
    Node *ptr = this->head;
    while (ptr != NULL && ptr->data != item) {
        ptr = ptr->next;
        idx++;
    }
    if (ptr == NULL) return -1;
    return idx;
}

/* Check if item appears in the list */
template<class T>
bool DLinkedList<T>::contains(const T& item) {
    return (this->indexOf(item) != -1);    
}

/* Remove element at index and return removed value */
template <class T>
T DLinkedList<T>::removeAt(int index)
{
    int idx = index;
    Node *ptr = this->head;
    while (idx--) {
        ptr = ptr->next;
    }
    if (ptr->previous != NULL)
        ptr->previous->next = ptr->next;
    if (ptr->next != NULL)
        ptr->next->previous = ptr->previous;
    
    if (index >= this->count - 1) {
        this->tail = ptr->previous;
    }
    if (index <= 0) {
        this->head = ptr->next;
    }
    this->count--;
    int retval = ptr->data;
    return retval;
}

/* Remove the first apperance of item in list and return true, otherwise return false */
template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    Node *ptr = this->head;
    while (ptr != NULL && ptr->data != item) {
        ptr = ptr->next;
    }
    if (!ptr) return false;

    if (ptr->previous != NULL)
        ptr->previous->next = ptr->next;
    if (ptr->next != NULL)
        ptr->next->previous = ptr->previous;
    
    if (ptr->next == NULL) {
        this->tail = ptr->previous;
    }
    if (ptr->previous == NULL) {
        this->head = ptr->next;
    }
    this->count--;

    return true;    
}

/* Remove all elements in list */
template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    this->head = this->tail = NULL;
    this->count = 0;
}
