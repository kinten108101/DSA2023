#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include "../Utils/utils.h"

template <class T>
class IteratorBackend {
public:
	IteratorBackend() {};
	virtual ~IteratorBackend() {};

    virtual T& operator*() {
        throw utils::NotImplementedException("operator*");
    }

	virtual const IteratorBackend<T>& operator++() {
        return *this;
    } // prefix increment

	virtual const IteratorBackend<T>& operator++(int) {
        return *this;
    }; // postfix increment

	virtual const IteratorBackend<T>& operator+(int) {
        return *this;
    };

	virtual bool operator!=(const IteratorBackend<T>& rhs) {
        return true;
    };

	virtual bool operator==(const IteratorBackend<T>& rhs) const {
		if (typeid(*this) == typeid(rhs) && this->of_same_type(rhs)) {
			return true;
		} else {
			return false;
		}
	}
    virtual T& value() {
        throw utils::NotImplementedException("value");
    };

protected:
	virtual bool of_same_type(const IteratorBackend<T>&) const {
		return true;
	};
};

template <class T>
class Iterator {
protected:
	IteratorBackend<T> *it;
public:
	Iterator(): it(nullptr) {
		throw std::logic_error("");
	}
	Iterator(IteratorBackend<T> *it): it(it) {}

    virtual ~Iterator() {
        if (this->it) delete this->it;
    }

	virtual Iterator<T> operator=(const Iterator<T>& rhs) {
        if (this->it == rhs.it) return *this;
		if (this->it) {
			delete this->it;
		}
		this->it = rhs.it;
		return *this;
	}

	virtual bool operator!=(const Iterator<T>& rhs) {
		if (*(this->it) != *(rhs.it)) return true;
		return false;
	}

    virtual const Iterator<T>& operator++() {
        this->it->operator++(); 
        return *this;
    }

    virtual Iterator<T> operator++(int) const {
        auto &newit = (*(this->it))++;
        return Iterator<T>((IteratorBackend<T> *)&(newit));
    }

	T& operator*() {
		if (this->it) {
            return this->it->operator*();
        } else {
            throw utils::NullPointerException("this->it");
        }
	}

    virtual T& value() {
        if (this->it) return this->it->value();
        else throw utils::NullPointerException("this->it");
    }
};


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

    class SLinkedListIteratorBackend : public IteratorBackend<T> {
    protected:
        Node *data;
    public:
        SLinkedListIteratorBackend(Node *data): data(data) {}
        virtual ~SLinkedListIteratorBackend() {}

        virtual long operator&() {
            return (long)data;
        }

        virtual T& operator*() {
            return (this->data->data);
        }

        virtual SLinkedListIteratorBackend& operator++() {
            T a = (this->operator*());
            this->data = this->data->next;
            return (*this);
        }

        virtual SLinkedListIteratorBackend& operator++(int) {
            SLinkedListIteratorBackend *ret = new SLinkedListIteratorBackend(this->data);
            this->data = this->data->next;
            return *ret;
        }

        virtual SLinkedListIteratorBackend& operator+(int num) {
            Node *ptr = this->data;
            for (int i = 0; i < num; i++) {
                ptr = ptr->next;
            }
            return *(new SLinkedListIteratorBackend(ptr)); 
        }

        virtual bool operator!=(const IteratorBackend<T>& rhs) {
            if ((typeid(*this) != typeid(rhs))) return true;
            if (this->data != ((const SLinkedListIteratorBackend&)rhs).data) return true;
        	return false;
        }

        virtual bool operator!=(const SLinkedListIteratorBackend& rhs) {
            return false;
        }

        virtual bool of_same_type(const IteratorBackend<T>& ptr) const {
            return (typeid(*this) == typeid(&ptr));
        }

        virtual T& value() {
            return this->data->data;
        }
    };

    Iterator<T> begin() {
        return Iterator<T>(new SLinkedListIteratorBackend(this->head));
    }

    Iterator<T> end() {
        return Iterator<T>(new SLinkedListIteratorBackend(nullptr));
    }
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
	SLinkedList<int> list;
	list.add(9);
	list.add(2);
    list.add(3);
    for (auto val : list) {
        std::cout << std::setw(5) << val << std::endl;
    }
	for (auto it = list.begin(); it != list.end(); ++it) {
		std::cout << std::setw(5) << *it << std::endl;
	}
	return 0;
}