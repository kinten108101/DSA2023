# Chapter 9: Iterator

## Built-in C++ Iterator Interface

Iterator pattern. For a class List, implement an interface with methods `begin` and `end`. For an class Iterator, implement some operator overloading (operator+, operator-, operator++, operator--, compare operators < > <= >= == !=). Then, do like so:

```cpp
for (auto it = list.begin(); it != list.end(); i++) {}
```

In C++ we can write the following shorthand expression which will be expanded into the above expression[^for-expansion]:

```cpp
for (T i : list) {}
```

This is also called a for-each loop.

A limitation in this expression is that you can only iterate forward.

Forward iterator is most common. A random-access iterator supports iterating in all directions.

## Composition pattern

An alternative to the inheritance pattern. It allows for more control when building classes, but you have to write more boilerplate code.

In inheritance, the parent's interface, including public and protected props and methods, is thrust into the child's. This means that the child cannot remove any part of that interface, only add to it.

In composition, the parent is available as a protected object for the child to use. To have the parent's interface, the child has to implement it. This results in more boilerplate code, but functionally it's the smae, and the child gets the freedom to choose which part of the interface to have, and which part not.

```cpp
class IteratorBackend {
	
}

class ArrayIteratorBackend : protected IteratorBackend {
	
}

class LListIteratorBackend : protected IteratorBackend {
	
}

class Iterator {
protected:
	IteratorBackend *backend;
public:
	Iterator(IteratorBackend *backend): backend(backend) {};
}

int main() {
	Iterator it = new Iterator(new ArrayIteratorBackend());
}

```

Array of pointers, I mistook this for array of values...
```cpp
ToyBox *box[5];
```

Copy constructors T::T(T&) are also implicitly defined as default constructor.

[^for-expansion]: Expanded when, compile time or?