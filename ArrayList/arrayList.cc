#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "../Utils/utils.h"

using namespace std;

template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    ArrayList(){capacity = 5; count = 0; data = new T[5];}
    ~ArrayList(){ delete[] data; }
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item); // Provided
    bool    contains(T item); // Provided
    T       removeAt(int index);
    bool    removeItem(T item);
    void    ensureCapacity(int index);
    string toString();
};

template <class T>
string ArrayList<T>::toString() {
    string str("");
    str += "[";
    for (int i = 0; i < this->count; i++) {
        if (i == 0) str += to_string(this->data[i]);
        else str += ", " + to_string(this->data[i]);
    }
    str += "]";
    return str;
}

void ensureRange(int access_idx, int count) {
    if (access_idx < 0 || access_idx > count) {
        throw std::out_of_range("the input index is out of range!");
    }
}

template<class T>
void ArrayList<T>::ensureCapacity(int cap){
    /* 
        if cap == capacity: 
            new_capacity = capacity * 1.5;
            create new array with new_capacity
        else: do nothing
    */
    if (cap >= this->capacity) {
        int new_capacity = capacity * 1.5;
        T* new_data = new int[new_capacity];
        int i = 0;
        for (; i<this->count; i++) {
            new_data[i] = data[i];
        }
        for (; i<new_capacity; i++) {
            new_data[i] = 0;
        }
        delete this->data;
        this->data = new_data;
        this->capacity = new_capacity;
    }
}

template <class T>
void ArrayList<T>::add(T e) {
    this->ensureCapacity(this->count);
    this->data[this->count++] = e;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
    this->ensureCapacity(this->count);
    ensureRange(index, this->count);
    for (int idx = this->count, end = index + 1; idx >= end; idx--) {   
        this->data[idx] = this->data[idx - 1];
    }
    this->data[index] = e;
    this->count++;
}

template<class T>
int ArrayList<T>::size() {
    return this->count;
}

template<class T>
bool ArrayList<T>::empty() {
    if (this->count <= 0) return true;
    else return false;
}



template<class T>
T ArrayList<T>::get(int index) {
    ensureRange(index, this->count);
    return this->data[index];
}

template<class T>
void ArrayList<T>::set(int index, T e) {
    ensureRange(index, this->count);   
    this->data[index] = e;
}

template<class T>
void ArrayList<T>::clear(){
    delete this->data;
    this->data = new int[5];
    this->count = 0;
    this->capacity = 5;
}

template<class T>
T ArrayList<T>::removeAt(int index){
    ensureRange(index, this->count);
    T element = this->data[index];
    for (int i = index; i < this->count - 1; i++) {
        this->data[i] = this->data[i + 1];
    }
    this->count--;
    return element;
}

template<class T>
bool ArrayList<T>::removeItem(T item){
     /* Remove the first apperance of item in array and return true, otherwise return false */
    int i = 0;
    for (; i <= this->count; i++) {
        if (i == this->count) break;
        if (this->data[i] == item) {
            break;
        }
    }
    if (i < this->count) {
        for (int j = i; j < this->count - 1; j++) {
            this->data[j] = this->data[j + 1];
        }
        this->count--;
        return true;
    }
    return false;
}

int main() {
    utils::runtest("Add, size, ensureCapacity",
    {
        []() {
            ArrayList<int> arr;
            int size = 10;

            for(int index = 0; index < size; index++){
                arr.add(index);
            }

            cout << arr.toString() << '\n';
            cout << arr.size();
            return 0;
        },
        []() {
            ArrayList<int> arr;
            int size = 20;

            for(int index = 0; index < size; index++){
                arr.add(0, index);
            }

            cout << arr.toString() << '\n';
            cout << arr.size() << '\n';
            return 0;
        },
        []() {
            ArrayList<int> arr;
            int size = 20;

            for (int index = 0; index < size; index++) {
                arr.add(arr.size(), index);
            }

            cout << arr.toString() << '\n';
            cout << arr.size() << '\n';
            arr.ensureCapacity(20);
            return 0;
        },
        []() {
            ArrayList<int> arr;
            int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
            int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
            for (int idx = 0; idx < 8; idx++){
               arr.add(index[idx], values[idx]);
            }

            cout << arr.toString() << '\n';
            cout << arr.size() << '\n';
            arr.ensureCapacity(6);
            return 0;
        }
    });

    utils::runtest("removeAt, removeItem, clear", {
        []() {
            ArrayList<int> arr;

            for (int i = 0; i < 10; ++i) {
                arr.add(i);
            }
            arr.removeAt(0);

            cout << arr.toString() << '\n';
            cout << arr.size();
            if (arr.toString() != "[1, 2, 3, 4, 5, 6, 7, 8, 9]" || arr.size() != 9) return 1;
            return 0;
        },
        []() {
            ArrayList<int> arr;

            for (int i = 0; i < 10; ++i) {
                arr.add(i);
            }
            arr.removeAt(9);

            cout << arr.toString() << '\n';
            cout << arr.size();

            if (arr.toString() != "[0, 1, 2, 3, 4, 5, 6, 7, 8]" || arr.size() != 9) return 1;
            return 0;
        },
        []() {
            ArrayList<int> arr;

            for (int i = 0; i < 10; ++i) {
                arr.add(i);
            }
            arr.removeAt(1);

            cout << arr.toString() << '\n';
            cout << arr.size();
            if (arr.toString() != "[0, 2, 3, 4, 5, 6, 7, 8, 9]" || arr.size() != 9) return 1;
            return 0;
        },
        []() {
            ArrayList<int> arr;

            for (int i = 0; i < 10; ++i) {
                arr.add(i);
            }
            arr.removeItem(0);

            cout << arr.toString() << '\n';
            cout << arr.size();
            if (arr.toString() != "[1, 2, 3, 4, 5, 6, 7, 8, 9]" || arr.size() != 9) return 1;
            return 0;
        },
        []() {
            ArrayList<int> arr;
            int size = 10;
            for(int idx=0; idx < size; idx++){
                arr.add(idx);
            }
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
 
            arr.clear();
            for(int idx=0; idx < 8; idx++)
                arr.add(values[idx]);

            //removeAt:
            for(int idx=0; idx < 8; idx++){
                int idxRemoved = index[idx];
                arr.removeAt(idxRemoved);
                //check expected values
            }

            cout << arr.toString() << '\n';
            cout << arr.size();
            if (arr.toString() != "[]" || arr.size() != 0) return 1;
            return 0;
        }
    });
    return 0;
}