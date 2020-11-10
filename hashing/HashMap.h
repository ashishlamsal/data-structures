#pragma once

#include <iterator>

#include "Vector.h"
#include "HashCode.h"

template <typename KeyType, typename ValueType>
class HashMap {
private:
    static const int INITIAL_BUCKET_COUNT = 101;
    static const int MAX_LOAD_PERCENTAGE = 70;

    struct Entry {
        KeyType key;
        ValueType value;
        Entry* next;
    };

    Vector<Entry*> buckets;
    int nBuckets;
    int numEntries;

private:
    void createBuckets(int nBuckets);
    void deleteBuckets(Vector <Entry*>& buckets);
    void expandAndRehash();
    Entry* findEntry(int bucket, const KeyType& key) const;
    Entry* findEntry(int bucket, const KeyType& key, Entry*& parent) const;
    void deepCopy(const HashMap& src);

public:
    HashMap();
    HashMap(const HashMap& src);
    HashMap& operator=(const HashMap& src);
    virtual ~HashMap();

    void clear();
    int size() const;
    bool isEmpty() const;

    void put(const KeyType& key, const ValueType& value);
    ValueType get(const KeyType& key) const;
    bool containsKey(const KeyType& key) const;
    void remove(const KeyType& key);

    ValueType& operator[](const KeyType& key);
    ValueType operator[](const KeyType& key) const;

    class iterator : public std::iterator<std::input_iterator_tag, Entry> {
    private:
        const HashMap* map;          /* Pointer to the map           */
        int bucket;                  /* Index of current bucket      */
        Entry* current;              /* Current cell in bucket chain */

    public:
        iterator() {}

        iterator(const HashMap* map, bool end) {
            this->map = map;
            if (end) {
                bucket = map->nBuckets;
                current = nullptr;
            }
            else {
                bucket = 0;
                current = map->buckets.get(bucket);
                while (current == nullptr && ++bucket < map->nBuckets) {
                    current = map->buckets.get(bucket);
                }
            }
        }

        iterator(const iterator& it) {
            map = it.map;
            bucket = it.bucket;
            current = it.current;
        }

        iterator& operator++() {
            current = current->next;
            while (current == nullptr && ++bucket < map->nBuckets) {
                current = map->buckets.get(bucket);
            }
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            operator++();
            return copy;
        }

        bool operator==(const iterator& rhs) {
            return map == rhs.map && bucket == rhs.bucket && current == rhs.current;
        }

        bool operator!=(const iterator& rhs) {
            return !(*this == rhs);
        }

        Entry operator*() {
            return *current;
        }

        Entry* operator->() {
            return current;
        }
    };

    iterator begin() const {
        return iterator(this, false);
    }

    iterator end() const {
        return iterator(this, true);
    }
};

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::createBuckets(int nBuckets) {
    if (nBuckets == 0) nBuckets = 1;
    buckets = Vector<Entry*>(nBuckets, nullptr);
    this->nBuckets = nBuckets;
    numEntries = 0;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::deleteBuckets(Vector <Entry*>& buckets) {
    for (int i = 0; i < buckets.size(); i++) {
        Entry* current = buckets[i];
        while (current != nullptr) {
            Entry* np = current->next;
            delete current;
            current = np;
        }
        buckets[i] = nullptr;
    }
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::expandAndRehash() {
    Vector<Entry*>oldBuckets = buckets;
    createBuckets(oldBuckets.size() * 2 + 1);
    for (int i = 0; i < oldBuckets.size(); i++) {
        for (Entry* current = oldBuckets[i]; current != nullptr; current = current->next) {
            put(current->key, current->value);
        }
    }
    deleteBuckets(oldBuckets);
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::Entry*
HashMap<KeyType, ValueType>::findEntry(int bucket, const KeyType& key) const {
    Entry* dummy;
    return findEntry(bucket, key, dummy);
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::Entry*
HashMap<KeyType, ValueType>::findEntry(int bucket, const KeyType& key, Entry*& parent) const {
    parent = nullptr;
    Entry* current = buckets.get(bucket);
    while (current != nullptr && key != current->key) {
        parent = current;
        current = current->next;
    }
    return current;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::deepCopy(const HashMap& src) {
    createBuckets(src.nBuckets);
    for (int i = 0; i < src.nBuckets; i++) {
        for (Entry* current = src.buckets.get(i); current != nullptr; current = current->next) {
            put(current->key, current->value);
        }
    }
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap() {
    createBuckets(INITIAL_BUCKET_COUNT);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
    deleteBuckets(buckets);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap& src) {
    deepCopy(src);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator=(const HashMap& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

template <typename KeyType, typename ValueType>
int HashMap<KeyType, ValueType>::size() const {
    return numEntries;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() const {
    return size() == 0;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
    (*this)[key] = value;
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::get(const KeyType& key) const {
    Entry* current = findEntry(hashCode(key) % nBuckets, key);
    if (current == nullptr) return ValueType();
    return current->value;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::containsKey(const KeyType& key) const {
    return findEntry(hashCode(key) % nBuckets, key) != nullptr;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::remove(const KeyType& key) {
    int bucket = hashCode(key) % nBuckets;
    Entry* parent;
    Entry* current = findEntry(bucket, key, parent);
    if (current != nullptr) {
        if (parent == nullptr) {
            buckets[bucket] = current->next;
        }
        else {
            parent->next = current->next;
        }
        delete current;
        numEntries--;
    }
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::clear() {
    deleteBuckets(buckets);
    numEntries = 0;
}

template <typename KeyType, typename ValueType>
ValueType& HashMap<KeyType, ValueType>::operator[](const KeyType& key) {
    int bucket = hashCode(key) % nBuckets;
    Entry* current = findEntry(bucket, key);
    if (current == nullptr) {
        if (numEntries > MAX_LOAD_PERCENTAGE * nBuckets / 100.0) {
            expandAndRehash();
            bucket = hashCode(key) % nBuckets;
        }
        current = new Entry;
        current->key = key;
        current->value = ValueType();
        current->next = buckets[bucket];
        buckets[bucket] = current;
        numEntries++;
    }
    return current->value;
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::operator[](const KeyType& key) const {
    return get(key);
}