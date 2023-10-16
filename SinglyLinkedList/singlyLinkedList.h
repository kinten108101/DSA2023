#include <iostream>
#include <stdexcept>
#include "../Utils/utils.h"

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList();
    ~SLinkedList();
    std::string toString();
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
    void bubbleSort();
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
std::string SLinkedList<T>::toString() {
    std::string str("");
    str += "[";
    for (Node *p = this->head; p != nullptr; p = p->next) {
        if (p == this->head) str += std::to_string(p->data);
        else str += "," + std::to_string(p->data);
    }
    str += "]";
    return str;
}

template <class T>
SLinkedList<T>::SLinkedList(): head(nullptr), tail(nullptr), count(0) {
}

template <class T>
SLinkedList<T>::~SLinkedList() {
    if (this->count <= 0) return;
    Node *prev = this->head, *p = this->head->next;
    for (; p != nullptr; p = p->next) {
        delete prev;
        prev = p;
    }
    delete this->tail;
}

/* Insert an element into the end of the list. */
template <class T>
void SLinkedList<T>::add(const T& e) {
    Node *newnode = new Node(e, nullptr);
    if (this->count == 0) {
        this->head = newnode;
        this->tail = newnode;
    } else {
        this->tail->next = newnode;
        this->tail = newnode;
    }
    this->count++;
}

/* Insert an element into the list at given index. */ 
template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    if (index < 0 || index > this->count) {
        throw std::out_of_range("");
    }
    Node *newnode = new Node(e, nullptr);
    Node *p = this->head, *prev = nullptr;
    for (int i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    if (prev != nullptr) prev->next = newnode;
    newnode->next = p;
    if (prev == nullptr) this->head = newnode;
    if (p == nullptr) this->tail = newnode;
    this->count++;
}

/* Return the length (size) of list */ 
template<class T>
int SLinkedList<T>::size() {
    return this->count;
}

/* Remove element at index and return removed value */
template <class T>
T SLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("");
    }
    Node *p = this->head, *prev = nullptr;
    for (int i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    if (prev == nullptr)
        this->head = this->head->next;
    if (p == this->tail) {
        this->tail = prev;
    }
    if (prev != nullptr)
        prev->next = p->next;
    this->count--;
    return p->data;
}

/* Remove the first apperance of item in list and return true, otherwise return false */
template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    Node *p = this->head, *prev = nullptr;
    for (; p != nullptr;) {
        if (p->data == item) break;
        prev = p;
        p = p->next;
    }
    if (p == nullptr) return false;
    if (p->data == item) {
        if (prev == nullptr)
            this->head = this->head->next;
        if (p == this->tail) {
            this->tail = prev;
        }
        if (prev != nullptr)
            prev->next = p->next;
        this->count--;
        return true;
    }
    return false;
}

/* Remove all elements in list */
template<class T>
void SLinkedList<T>::clear(){
    Node *prev = this->head, *p = this->head->next;
    for (; p != nullptr; p = p->next) {
        delete prev;
        prev = p;
    }
    delete this->tail;
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template <class T>
T SLinkedList<T>::get(int index) {
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("");
    }
    Node *p = this->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

/* Assign new value for element at given index in the list */
template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("");
    }
    Node *p = this->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    p->data = e;
}

template <class T>
bool SLinkedList<T>::empty() {
    return this->count <= 0;
}

/* Return the first index wheter item appears in list, otherwise return -1 */
template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    Node *p = this->head;
    int i = 0;
    for (; p != nullptr; p = p->next, i++) {
        if (p->data == item) break;
    }
    if (p == nullptr) return -1;
    return i;
}

/* Check if item appears in the list */
template<class T>
bool SLinkedList<T>::contains(const T& item) {
    Node *p = this->head;
    for (; p != nullptr; p = p->next) {
        if (p->data == item) return true;
    }
    return false;
}

template <class T>
void SLinkedList<T>::bubbleSort()
{
    for (int i = this->size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            Node *node_prev = nullptr;
            Node *node_first = this->head;
            for (int k = 0; k < j; k++) {
                node_prev = node_first;
                node_first = node_first->next;
            }
            
            Node *node_second = node_first->next;
            
            if (*node_first <= *node_second) continue;
            
            Node *node_next = node_second->next;
            node_prev->next = node_second;
            node_second->next = node_first;
            node_first->next = node_next;
        }
    }
}