#include <iostream>
using namespace std;

int hashFunction(int key, int capacity) {
  return key % capacity;
}

template <class K, class V>
class XHashMap {
public:
  class Entry {
  public:
    K key;
    V value;
    Entry *next;

    Entry
    ( K key
    , V value
    , Entry *next = 0
    ) {
      this->key   = key;
      this->value = value;
      this->next  = next;
    }
  };

  XHashMap() {
    this->capacity = 10;
    this->count    = 0;
    this->table    = new Entry*[capacity];
    for (int i = 0; i < this->capacity; i++) {
      this->table[i] = 0;
    }
  }

  ~XHashMap() {
    for (int idx = 0; idx < this->capacity; idx++) {
      Entry *entry = this->table[idx];
      while (entry != nullptr) {
        Entry *next = entry->next;
        delete entry;
        entry = next;
      }
    }
    delete [] table;
  }

  //TODO: Compute the index using the hash function
  //TODO: Check if the key exists in the linked list at the index, update if found
  //TODO: If the key doesn't exist, create and insert a new entry
  //TODO: Increment the count and ensure load factor by resizing if needed
  void put(K key, V value) {
    int index = hashFunction(key, this->capacity);
    auto *entry = new Entry(key, value);
    auto *keyOccupation = this->table[index];

    if (keyOccupation) {
      Entry *uprev = nullptr;
      Entry *u = keyOccupation;
      while (u && u->key != entry->key) {
        uprev = u;
        u = u->next;
      }
      if (u == nullptr) {
        entry->next = keyOccupation;
        this->table[index] = entry;
        this->count++;
      } else {
        u->value = entry->value;
      }
    } else {
      this->table[index] = entry;
      this->count++;
    }
    this->ensureLoadFactor(this->count);
  }

  //TODO: Calculate the maximum allowed size based on the load factor (0.75 * capacity)
  //TODO: If the current size exceeds or equals the max allowed size, trigger rehashing
  //TODO: Calculate the new capacity (1.5 times the old capacity)
  //TODO: Call the rehash function with the new capacity
  void ensureLoadFactor(int current_size) {
    int maxsize = 0.75 * this->capacity;
    if (current_size >= maxsize) {
      int newcapacity = 1.5 * this->capacity;
      rehash(newcapacity);
    }
  }

  //TODO: Store the current table and capacity
  //TODO: Create a new table with the new capacity and update the capacity
  //TODO: Initialize the new table with nullptr values
  //TODO: For each index in the old table:
  //      - Traverse the linked list at that index
  //      - Recompute the new index for each entry using the new capacity
  //      - Insert the entry into the new table at the recomputed index
  //TODO: Delete all entries in the old table by traversing each linked list and deleting nodes
  //TODO: Delete the old table array
  void rehash(int newCapacity) {
    Entry **newtable = new Entry*[newCapacity];
    // TODO(kinten): Is this prep step needed? pointers should be initialized to 0 already?
    for (int i = 0; i < newCapacity; i++) {
      newtable[i] = nullptr;
    }
    for (int i = 0; i < this->capacity; i++) {
      Entry *u = this->table[i];
      while (u != nullptr) {
        int newi = hashFunction(u->key, newCapacity);
        Entry *occupation = newtable[newi];
        if (occupation) {
          newtable[newi] = new Entry(u->key, u->value, occupation);
        } else {
          newtable[newi] = new Entry(u->key, u->value);
        }
        Entry *unext = u->next;
        delete u;
        u = unext;
      }
    }
    delete [] this->table;
    this->table    = newtable;
    this->capacity = newCapacity;
    this->count    = this->count;
  }

  // Calculate the index using the hash function.
  // Access and traverse the linked list at that index.
  // If the current entry's key matches, return its value.
  // If not found, throw std::out_of_range("Key not found");
  V& get(K key) {
    int index = hashFunction(key, this->capacity);
    Entry *u = this->table[index];
    while (u != nullptr) {
      if (u->key == key)
        return u->value;
      u = u->next;
    }
    throw std::out_of_range("Key not found");
  }

  /*
    An index need to find by using the hash function,
    then find the Entry of this index
    Check if the key already exists. If yes, remove the key from the table
    If the key doesn't exist, throw out_of_range("Key not found");
  */
  V remove(K key) {
    int index = hashFunction(key, this->capacity);
    Entry *uprev = nullptr;
    Entry *u = this->table[index];
    while (u != nullptr) {
      if (u->key == key)
        break;
      uprev = u;
      u = u->next;
    }
    if (u == nullptr)
      throw std::out_of_range("Key not found");
    if (uprev == nullptr) {
      V value = u->value;
      delete u;
      this->table[index] = nullptr;
      this->count--;
      return value;
    } else {
      V value = u->value;
      Entry *unext = u->next;
      delete u;
      uprev->next = unext;
      this->count--;
      return value;
    }
  }

  void printTable() const {
    cout << "------------The hash table is shown below------------\n";
    for (int i = 0; i < capacity; i++) {
      Entry* entry = table[i];
      cout << "Index " << i << ": ";
      while (entry != 0) {
        cout << "(" << entry->key << ", " << entry->value << ") ";
        entry = entry->next;
      }
      cout << endl;
    }
    cout << "-----------------------------------------------------\n";
  }

private:
  Entry **table;
  int capacity;
  int count;
};

void tc_sample_0() {
  XHashMap<int, int> map;
  map.put(6, 100);
  map.put(6, 100);
  map.printTable();
}

void tc_sample_1() {
  XHashMap<int, int> map;
  map.put(0, 20);
  map.put(10, 100); // adding not replacing
  map.put(0, 10);
  map.printTable();          
}

void tc_sample_2() {
  XHashMap<int, int> map;
  map.put(1, 15);
  map.put(1, 200); // updating new value for existing index
  map.printTable();
}

void tc_rehash() {
  XHashMap<int, int> map;
  map.put(4, 20);
  map.put(6, 100);
  map.put(6, 100);
  map.put(1, 10);
  map.rehash(5);
  map.printTable();
}

void tc_epic() {
  XHashMap<int, int> map;
  map.put(132, 664);
  map.put(312, 305);
  map.put(232, 743);
  map.put(322, 101);
  map.put(452, 651);
  map.put(542, 836);
  map.put(672, 129);
  map.put(762, 432);
  map.put(892, 923);
  map.put(982, 489);
  map.printTable();
}

#include <vector>

void tc_get_0() {
  XHashMap<int, int> map;
  map.put(20, 95);
  vector<int> keys = {20};
  for(int key: keys){
    try{
      cout << "Value for key " << key <<": " << map.get(key) << endl;
    }
    catch (std::out_of_range& e){
      cout << e.what() << endl;
    }
  }
}

void tc_remove_0() {
  XHashMap<int, int> map;
  map.put(68, 57);
  vector<int> keys = {68};  // Update the keys vector to hold the new key
  for (int key : keys) {
    try {
      cout << "Remove for key = " << key << ", value = " << map.remove(key) << endl;
    }
    catch (std::out_of_range& e) {  // Catch the out_of_range exception
      cout << e.what() << endl;   // Print the exception message
    }
  }
}

void tc_remove_1() {
  XHashMap<int, int> map;
  map.put(92, 32);
  map.put(34, 86);
  vector<int> keys = {92, 51, 34};  // Include all keys in the vector
  for (int key : keys) {
    try {
      cout << "Remove for key = " << key << ", value = " << map.remove(key) << endl;
    }
    catch (std::out_of_range& e) {  // Catch the out_of_range exception
      cout << e.what() << endl;   // Print the exception message
    }
  }
}

void tc_remove_2() {
  XHashMap<int, int> map;
  map.put(83, 87);
  map.put(4, 74);
  map.put(56, 29);
  vector<int> keys = {83, 4, 77, 28, 56};  // Update the keys vector with the new keys
  for (int key : keys) {
    try {
      cout << "Remove for key = " << key << ", value = " << map.remove(key) << endl;
    }
    catch (std::out_of_range& e) {  // Catch the out_of_range exception
      cout << e.what() << endl;   // Print the exception message
    }
  }
}

void (*funcs[99])() = {
  /* tc_0 */ tc_sample_0,
  /* tc_1 */ tc_sample_1,
  /* tc_2 */ tc_sample_2,
  /* tc_3 */ tc_rehash,
  /* tc_4 */ tc_epic,
  /* tc_5 */ tc_get_0,
  /* tc_6 */ tc_remove_0,
  /* tc_7 */ tc_remove_1,
  /* tc_8 */ tc_remove_2,
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "missing argument TC_IDX" << endl;
    return 1;
  }
  int tc_idx = stoi(argv[1]);
  funcs[tc_idx]();
  return 0;
}
