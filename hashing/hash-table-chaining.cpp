// Collision resolution : Separate chaining with linked lists

#include <iostream>
#include <string>
#include <list>

const int MAXSIZE = 5;

class HashTable {
private:
    class Entry {
    public:
        int key;
        std::string value;
        Entry(int key, const std::string& value) :key(key), value(value) {}
    };
    std::list<HashTable::Entry>* entries;

private:
    int hash(int);
    std::list<HashTable::Entry>& getBucket(int);

public:
    HashTable();
    ~HashTable();
    void put(int, const std::string&);
    std::string get(int);
    void remove(int);
    void display();
};

HashTable::HashTable() {
    entries = new std::list<HashTable::Entry>[MAXSIZE];
}

HashTable::~HashTable() {
    delete[] entries;
}

int HashTable::hash(int key) {
    return std::abs(key) % MAXSIZE;
}

std::list<HashTable::Entry>& HashTable::getBucket(int key) {
    return entries[hash(key)];
}

void HashTable::put(int key, const std::string& value) {
    std::list<HashTable::Entry>& bucket = getBucket(key);

    if (!bucket.empty()) {
        std::list<HashTable::Entry>::iterator itr;
        for (itr = bucket.begin(); itr != bucket.end(); itr++) {
            if (itr->key == key) {
                itr->value = value;
                return;
            }
        }
    }

    bucket.push_back(Entry(key, value));
}

std::string HashTable::get(int key) {
    std::list<HashTable::Entry>& bucket = getBucket(key);

    if (!bucket.empty()) {
        std::list<HashTable::Entry>::const_iterator itr;
        for (itr = bucket.begin(); itr != bucket.end(); itr++) {
            if (itr->key == key) {
                return itr->value;
            }
        }
    }

    return "Invalid Key";
}

void HashTable::remove(int key) {
    std::list<HashTable::Entry>& bucket = getBucket(key);

    if (!bucket.empty()) {
        std::list<HashTable::Entry>::const_iterator itr;
        for (itr = bucket.begin(); itr != bucket.end(); itr++) {
            if (itr->key == key) {
                bucket.erase(itr);
                return;
            }
        }
    }

    std::cout << "Invalid Key" << std::endl;
}

void HashTable::display() {
    std::cout << "HashTable : { ";
    for (int i = 0; i < MAXSIZE; i++) {
        if (!entries[i].empty()) {
            for (auto&& entry : entries[i]) {
                std::cout << entry.key << "=" << entry.value << " ";
            }
        }
    }
    std::cout << "}\n";
}

int main() {
    HashTable table;
    table.put(32, "Harry");
    table.put(23, "Ron");
    table.put(52, "Hermoine");
    table.put(230, "Dumbledore");
    table.put(24, "Minearva");
    std::cout << table.get(32) << std::endl;
    table.display();
    table.remove(52);
    table.remove(32);
    table.display();
    return 0;
}