#include <functional>
#include <stack>

#include <iostream>
#include <iomanip>
#include "../Utils/utils.h"
#include "../SinglyLinkedList/singlyLinkedList.h"

template <class T>
class Sorter {
public:
    virtual int compare(const T&, const T&) {
        throw utils::NotImplementedException("compare");
    };
};

template <class T>
class CustomSorter : public Sorter<T> {
protected:
    std::function<int (const T&, const T&)> compare_func;
public:
    CustomSorter(std::function<int (const T&, const T&)> compare_func): compare_func(compare_func) {}

    virtual int compare(const T& a, const T&b) {
        return this->compare_func(a, b);
    }
};

template <class T>
class CombineSorter : public Sorter<T> {
protected:
    SLinkedList<Sorter<T>> sorters;
public:
    CombineSorter(Sorter<T> _sorters[]) {
        for (Sorter sorter : _sorters) {
            this->sorters.add(sorter);
        }
    }

    virtual int compare(const T& a, const T& b) {
        int result = 1;
        for (Sorter sorter : this->sorters) {
            result *= sorter.compare(a, b);
        }
        return result;
    }
};

template<class T>
T *default_pickpivot_func(T *arr, size_t size) {
    return arr + size/2;
}

template<class T>
int default_compare_func(const T& a, const T& b) {
    return a <= b;
}

template<class T>
void insertSort(
    T *data,
    size_t size,
    Sorter<T>& sorter,
    unsigned int step = 1
) {
    for (int i = 1; i < size; i+=step) {
        T tmp(std::move(data[i]));
        int j = 0;
        for (; j < i && sorter.compare(data[j], tmp); j+= step);
        if (j >= size) continue;
        for (int k = i; k > j; k-= step) {
            data[k] = std::move(data[k - 1]);
        }
        data[j] = tmp;
    }
}

template<class T>
void shellSort(
    T *arr,
    size_t size,
    std::function<int (const T&, const T&)> compare_func = default_compare_func<T>
) {
    std::stack<int> stack;
    stack.push(1);
    while (1) {
        int k = stack.top() * 3 + 1;
        if (k < size) stack.push(k);
        else break;
    }
    while (!stack.empty()) {
        int k = stack.top();
        for (int i = 0; i <= k; i++) {
            insertSort<T>(arr + i, size - i, compare_func, k);
        }
        stack.pop();
    }
}

template<class T>
void selectionSort(
    T *arr,
    size_t size,
    std::function<int (const T&, const T&)> compare_func = default_compare_func<T>
) {
    for (int i = 0; i < size; i++) {
        int min_idx = i;
        int j = i;
        for (; j < size; j++) {
            if (compare_func(arr[j], arr[min_idx])) min_idx = j;
        }
        T temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

template<class T>
void bubbleSort(
    T *arr,
    size_t size,
    std::function<int (const T&, const T&)> compare_func = default_compare_func<T>
) {
    for (int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (compare_func(arr[j], arr[j + 1])) continue;
            T temp(std::move(arr[j]));
            arr[j] = std::move(arr[j+1]);
            arr[j+1] = std::move(temp);
        }
    }
}

template<class T>
void quickSort(
    T *arr,
    size_t size,
    std::function<T* (T *, size_t)> pickpivot_func = default_pickpivot_func<T>,
    std::function<int (const T&, const T&)> compare_func = default_compare_func<T>
) {
    if (size < 1) return;
    T *pivot = pickpivot_func(arr, size);
    T *left = arr;
    T *right = arr + size - 1;
    while (left < right) {
        while (!compare_func(*pivot, *left) && left < right) left++;
        while (compare_func(*pivot, *right) && left < right) right--;
        if (left < right) {
            if (left == pivot) pivot = right;
            else if (right == pivot) pivot = left;
            T temp(std::move(*left));
            *left = std::move(*right);
            *right = std::move(temp);
        }
    }
    if (pivot != left) {
        T temp(std::move(*left));
        *left = std::move(*pivot);
        *pivot = std::move(temp);
    }
    quickSort(arr, left - arr, pickpivot_func, compare_func);
    quickSort(left + 1, size - (left - arr + 1), pickpivot_func, compare_func);
}

template<class T>
void mergeSort(
    T arr[],
    size_t size,
    std::function<int (const T&, const T&)> compare_func = default_compare_func<T>
) {
    if (size < 2) {
        return;
    }
    int size_sub = size / 2;
    mergeSort(arr, size_sub, compare_func);
    mergeSort(arr + size_sub, size - size_sub, compare_func);
    T *arr_sub = new T[size_sub];
    for (T *source = arr, 
           *end = arr + size_sub,
           *des = arr_sub;
        source != end;
    ) {
        *des++ = std::move(*source++);
    }
    T *target = arr,
      *left = arr_sub,
      *left_end = arr_sub + size_sub,
      *right = arr + size_sub,
      *right_end = arr + size;
    for (; left != left_end && right != right_end;) {
        if (compare_func(*left, *right)) {
            *target++ = std::move(*left++);
        } else {
            *target++ = std::move(*right++);
        }
    }

    for (; left != left_end;) {
        *target++ = std::move(*left++);
    }
    for (; right != right_end;) {
        *target++ = std::move(*right++);   
    }

    delete [] arr_sub;
}

template <class T>
int sort_test(
    int lower,
    int upper,
    T *sample,
    std::function<void (
        T*,
        size_t size,
        std::function<int (const T&, const T&)>
        )> funcs[]) {
    return 0;
}

int main() {
    int vals[5] = {};
    for (int i = 0; i < 5; i++) {
        vals[i] = rand() / 10000000;
        std::cout << std::setw(5) << vals[i];
    }
    std::cout << std::endl;
    shellSort(vals, 5);
    for (int i = 0; i < 5; i++) {
        std::cout << std::setw(5) << vals[i];
    }
    std::cout << std::endl;
    return 0;
}

// 
// auto time_begin = clock();
// auto time_end = clock();
// (time_begin - time_end) / CLOCKS_PER_SEC