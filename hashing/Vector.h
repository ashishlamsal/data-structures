#pragma once

#include <iostream>
#include <string>
#include <iterator>
#include <initializer_list>

template <typename ValueType>
class Vector {
private:
    ValueType* elements;        /* A dynamic array of the elements   */
    int capacity;               /* The allocated size of the array   */
    int count;                  /* The number of elements in use     */

private:
    void expandCapacity();
    void deepCopy(const Vector& src);

public:
    Vector(int n = 0);
    explicit Vector(int n, ValueType value);
    Vector(std::initializer_list<ValueType> list);
    Vector(const Vector& src);
    Vector& operator=(const Vector& src);
    virtual ~Vector();

    void clear();
    int size() const;
    bool isEmpty() const;

    const ValueType& get(int index) const;
    void set(int index, const ValueType& value);
    void insert(int index, ValueType value);
    void remove(int index);

    void push_back(ValueType value);
    void pop_back();
    void push_front(ValueType value);
    void pop_front();

    ValueType& operator[](int index);
    const ValueType& operator[](int index) const;

    Vector operator+(const Vector& v2) const;
    Vector operator+(const ValueType& value) const;
    Vector& operator+=(const Vector& v2);
    Vector& operator+=(const ValueType& value);

    class iterator : public std::iterator<std::random_access_iterator_tag, ValueType> {
    private:
        const Vector* vp;
        int index;
    public:
        iterator() :vp(nullptr) {}

        iterator(const iterator& it) {
            this->vp = it.vp;
            this->index = it.index;
        }

        iterator(const Vector* vp, int index) {
            this->vp = vp;
            this->index = index;
        }

        iterator& operator++() {
            index++;
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            operator++();
            return copy;
        }

        iterator& operator--() {
            index--;
            return *this;
        }

        iterator operator--(int) {
            iterator copy(*this);
            operator--();
            return copy;
        }

        bool operator==(const iterator& rhs) {
            return vp == rhs.vp && index == rhs.index;
        }

        bool operator!=(const iterator& rhs) {
            return !(*this == rhs);
        }

        bool operator<(const iterator& rhs) {
            extern void error(std::string msg);
            if (vp != rhs.vp) error("Iterators are in different vectors");
            return index < rhs.index;
        }

        bool operator<=(const iterator& rhs) {
            if (vp != rhs.vp)
                throw std::runtime_error("Iterators are in different vectors");
            return index <= rhs.index;
        }

        bool operator>(const iterator& rhs) {
            if (vp != rhs.vp)
                throw std::runtime_error("Iterators are in different vectors");
            return index > rhs.index;
        }

        bool operator>=(const iterator& rhs) {
            if (vp != rhs.vp)
                throw std::runtime_error("Iterators are in different vectors");
            return index >= rhs.index;
        }

        iterator operator+(const int& rhs) {
            return iterator(vp, index + rhs);
        }

        iterator operator+=(const int& rhs) {
            index += rhs;
            return *this;
        }

        iterator operator-(const int& rhs) {
            return iterator(vp, index - rhs);
        }

        iterator operator-=(const int& rhs) {
            index -= rhs;
            return *this;
        }

        int operator-(const iterator& rhs) {
            if (vp != rhs.vp)
                throw std::runtime_error("Iterators are in different vectors");
            return index - rhs.index;
        }

        ValueType& operator*() {
            return vp->elements[index];
        }

        ValueType* operator->() {
            return &vp->elements[index];
        }

        ValueType& operator[](int k) {
            return vp->elements[index + k];
        }
    };

    iterator begin() const {
        return iterator(this, 0);
    }

    iterator end() const {
        return iterator(this, count);
    }
};

template <typename ValueType>
Vector<ValueType>::Vector(int n) :count(0), capacity(n) {
    if (n < 0)
        throw std::runtime_error("Cannot create a Vector with a negative number of elements.");
    elements = (n == 0) ? nullptr : new ValueType[n];
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) : Vector(n) {
    for (int i = 0; i < n; i++) {
        elements[i] = value;
        count++;
    }
}

template <typename ValueType>
Vector<ValueType>::Vector(std::initializer_list<ValueType> list) : 
    Vector(static_cast<int>(list.size())) {
    for (auto&& value : list)
        elements[count++] = value;
}

template <typename ValueType>
Vector<ValueType>::Vector(const Vector& src) {
    deepCopy(src);
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator=(const Vector& src) {
    if (this != &src) {
        if (elements != nullptr)
            delete[] elements;
        deepCopy(src);
    }
    return *this;
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
    this->clear();
};

template <typename ValueType>
int Vector<ValueType>::size() const {
    return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
    if (elements != nullptr) 
        delete[] elements;
    count = capacity = 0;
    elements = nullptr;
}

template <typename ValueType>
const ValueType& Vector<ValueType>::get(int index) const {
    if (index < 0 || index >= count)
        throw std::out_of_range("get: index out of range");
    return elements[index];
}

template <typename ValueType>
void Vector<ValueType>::set(int index, const ValueType& value) {
    if (index < 0 || index >= count)
        throw std::out_of_range("set: index out of range");
    elements[index] = value;
}

template <typename ValueType>
void Vector<ValueType>::insert(int index, ValueType value) {
    if (count >= capacity) expandCapacity();
    if (index < 0 || index > count)
        throw std::out_of_range("insert: index out of range");

    for (int i = count; i > index; i--) {
        elements[i] = elements[i - 1];
    }
    elements[index] = value;
    count++;
}

template <typename ValueType>
void Vector<ValueType>::remove(int index) {
    if (index < 0 || index >= count)
        throw std::out_of_range("remove: index out of range");
    for (int i = index; i < count - 1; i++) {
        elements[i] = elements[i + 1];
    }
    count--;
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType value) {
    insert(count, value);
}

template <typename ValueType>
void Vector<ValueType>::pop_back() {
    remove(count - 1);
}

template <typename ValueType>
void Vector<ValueType>::push_front(ValueType value) {
    insert(0, value);
}

template <typename ValueType>
void Vector<ValueType>::pop_front() {
    remove(0);
}

template <typename ValueType>
ValueType& Vector<ValueType>::operator[](int index) {
    if (index < 0 || index >= count)
        throw std::out_of_range("Selection index out of range");
    //return elements[index];
    return const_cast<ValueType&>(static_cast<const Vector&>(*this)[index]);
}

template <typename ValueType>
const ValueType& Vector<ValueType>::operator[](int index) const {
    if (index < 0 || index >= count)
        throw std::out_of_range("Selection index out of range");
    return elements[index];
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator+(const Vector& v2) const {
    Vector<ValueType> result = *this;
    for (auto&& value : v2)
        result.push_back(value);
    return result;
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator +(const ValueType& value) const {
    Vector<ValueType> result = *this;
    return result += value;
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator+=(const Vector& v2) {
    for (auto&& value : v2)
        push_back(value);
    return *this;
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator+=(const ValueType& value) {
    this->push_back(value);
    return *this;
}

template <typename ValueType>
void Vector<ValueType>::deepCopy(const Vector& src) {
    count = capacity = src.count;
    elements = (capacity == 0) ? nullptr : new ValueType[capacity];
    for (int i = 0; i < count; i++) {
        elements[i] = src.elements[i];
    }
}

template <typename ValueType>
void Vector<ValueType>::expandCapacity() {

    capacity = std::max(1, capacity * 2);
    ValueType* array = new ValueType[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = std::move(elements[i]);
    }
    if (elements != nullptr)
        delete[] elements;
    elements = array;
    std::cout << "Copied  ";
    std::cout << "Capacity :" << capacity << std::endl;
}
