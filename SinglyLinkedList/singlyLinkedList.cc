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


int main() {
    utils::runtest("Add, Insert, Size", {
        []() {
            SLinkedList<int> list;
            int size = 10;

            for(int index = 0; index < size; index++){
                list.add(index);
            }

            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;
            int size = 10;

            for(int index = 0; index < size; index++){
                list.add(0, index);
            }

            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;
            int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
            int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
            for (int idx = 0; idx < 8; idx++){
               list.add(index[idx], values[idx]);
            }

            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;

            int values[] = { 13, 23, 7,  9,  8,  7,  50,  -1 };
            int index[] = { 0,  1,  1,  3,  2,  3,  5,  1 };

            for (int idx = 0; idx < 8; idx++) {
                list.add(index[idx], values[idx]);
            }

            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;

            int values[] = { 13, 23, 7,  9,  8,  7,  50,  -1 };
            int index[] = { 0,  1,  1,  3,  2,  3,  5,  1 };

            for (int idx = 0; idx < 8; idx++) {
                list.add(index[idx], values[idx]);
            }

            std::cout << list.size();

            return 0;
        },
    });
    utils::runtest("RemoveAt, RemoveItem, Clear", {
        []() {
            SLinkedList<int> list;

            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            if (!(list.get(0) == list.removeAt(0))) return 1;

            std::cout << list.toString();
            return 0;
        },
        []() {
             SLinkedList<int> list;

            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            if (list.get(5) != list.removeAt(5)) return 1;

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;

            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            if (!list.removeItem(0)) return 1;

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;

            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            if (!list.removeItem(5)) return 1;

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;

            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            if (list.removeItem(-5)) return 1;

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;
            if ( list.size() != 0 ) return 1;

            int size = 10;
            for(int idx=0; idx < size; idx++){
                list.add(idx);
            }
            if ( list.size() != size ) return 1;

            int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
            //                0    1    2    3   4   5    6    7
            int index[]    = {0,   1,   5,   3,  2,  1,   1,   0};

           /*                10,  15,  2,   6,  4,  7,   40,  8 //initial list
            *                15,  2,   6,   4,  7,  40,  8      //after removeAt 0
            *                15,  6,   4,   7,  40, 8      //after removeAt 1
            *                15,  6,   4,   7,  40   //after removeAt 5
            *                15,  6,   4,   40   //after removeAt 3
            *                15,  6,   40   //after removeAt 2
            *                15,  40   //after removeAt 1
            *                15,   //after removeAt 1
            *                {}  //after removeAt 0
            */
            int expvalues[][8]= {
                {15,  2,   6,   4,  7,  40,  8},
                {15,  6,   4,   7,  40, 8},
                {15,  6,   4,   7,  40},
                {15,  6,   4,   40 },
                {15,  6,   40},
                {15,  40},
                {15},
                {}
            };

            list.clear();
            if ( list.size() != 0 ) return 1;
            if ( list.empty() == false ) return 1;
            //
            for(int idx=0; idx < 8; idx++)
                list.add(values[idx]);
            if ( list.size() != 8 ) return 1;

            //removeAt:
            int count = 8;
            for(int idx=0; idx < 8; idx++){
                int idxRemoved = index[idx];
                list.removeAt(idxRemoved);
                if ( list.size() != (count - idx -1) ) return 1;
                //check expected values
                for(int c=0; c < (count - idx -1); c++ ){
                    int exp = expvalues[idx][c];
                    if (exp != list.get(c)) return 1;
                }
                std::cout << list.toString() << std::endl;
            }
            return 0;
        },
    });
    utils::runtest("Get, Set, Empty, IndexOf, Contains", {
        []() {
            SLinkedList<int> list;
            int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
            int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
            int expvalues[]= {8,  15, 2,  4,  7, 10,  40,  6}; 

            for (int idx = 0; idx < 8; idx++){
               list.add(index[idx], values[idx]);
            }

            if ( list.size() != 8 ) return 1;
                    
            for (int idx = 0; idx < 8; idx++){
                if ( list.get(idx) != expvalues[idx] ) return 1;
            }

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;

            if ( list.empty() == false ) return 1;
            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;
            for (int i = 0; i < 10; ++i) {
                list.add(i);
                }
                
            if ( list.empty() == true ) return 1;
            std::cout << list.toString();

            return 0;
        },
        []() {
            SLinkedList<int> list;
    
            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }
            for (int i = 10; i < 20; ++i) {
                if ( list.contains(i) == true ) return 1;
            }

            std::cout << list.toString();
            return 0;
        },
        []() {
            SLinkedList<int> list;
    
            for (int i = 0; i < 10; ++i) {
                list.add(i);
            }

            try {
                 list.get(100);
            }
            catch(std::out_of_range &e){
                 if ( 1 != 1 ) return 1; //pass
                 e.what();
            }

            return 0;
        },
    });
    return 0;
}