#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>

template<class T>
int default_compare_func(const T& a, const T& b) {
    return a <= b;
}

template <class T>
class Heap {
	T* elements;
	int count;
	int capacity;

	Heap(): elements(nullptr), count(0), capacity(0) {}

	void push(T item);
	void ensureCapacity(int);
	void reheapUp(int);
};

template<class T>
void Heap<T>::push(T item){
    this->ensureCapacity(this->count+1);
    this->elements[this->count] = item;
    this->count++;
    for (int i = 0; i < this->count; i++) {
        this->reheapUp(i);
    }
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    if (this->capacity <= minCapacity) {
        int newCap = this->capacity * 2;
        T* old = this->elements;
        this->elements = new T[newCap];
        for (int i = 0; i < this->count; i++) {
            this->elements[i] = old[i];
        }
        this->capacity = newCap;
        delete [] old;
    }
}

template<class T>
void Heap<T>::reheapUp(int idx){
    while (idx) {
		int parent_idx = (idx - 1) / 2;
		if (this->elements[idx] > this->elements[parent_idx]) {
			T temp(std::move(this->elements[idx]));
			this->elements[idx] = std::move(this->elements[parent_idx]);
			this->elements[parent_idx] = std::move(temp);
		}
		else return;
		idx = parent_idx;
	}
}

template <class T>
void heap_up(T *data, int idx) {
	while (idx) {
		int parent_idx = (idx - 1) / 2;
		if (data[idx] > data[parent_idx]) {
			T temp(std::move(data[idx]));
			data[idx] = std::move(data[parent_idx]);
			data[parent_idx] = std::move(temp);
		}
		else return;
		idx = parent_idx;
	}
}

template <class T>
void heap_down(T *data, int N, int idx = 0, std::function<int (const T&, const T&)> compare_func = default_compare_func<T>) {
	while (idx < N) {
		int max_idx = idx * 2 + 1;
		if (max_idx >= N) return;
		if (max_idx + 1 < N) {
			if (compare_func(data[max_idx], data[max_idx + 1])) max_idx++;
		}
		if (compare_func(data[idx], data[max_idx])) {
			T temp(std::move(data[idx]));
			data[idx] = std::move(data[max_idx]);
			data[max_idx] = std::move(temp);	
		} else return;
		idx = max_idx;
	}
}

template <class T>
void build_heap_v1(T *data, int N) {
	for (int i = 1; i < N; i++) heap_up(data, i);
}

template <class T>
void build_heap_v2(T *data, int N, std::function<int (const T&, const T&)> compare_func = default_compare_func<T>) {
	for (int i = N / 2; i > -1; i--) {
		heap_down(data, N, i, compare_func);
	}
}

template <class T>
void heap_sort(T *data, int N, std::function<int (const T&, const T&)> compare_func = default_compare_func<T>) {
	build_heap_v2(data, N);
	
	for (; N > 1;) {
		T temp(std::move(*data));
		*data = std::move(data[N - 1]);
		data[N - 1] = std::move(temp);
		heap_down(data, --N, 0, compare_func);
	}
	
}

int main() {
	int arr[7] = {5, 6, 1, 99, 21, 9, 10};
	for (int i = 0; i < 7; i++) {
		std::cout << std::setw(5) << arr[i];
	}
	std::cout << std::endl;
	heap_sort(arr, 7);
	for (int i = 0; i < 7; i++) {
		std::cout << std::setw(5) << arr[i];
	}
	std::cout << std::endl;
}