#include "Container.h"
#include "KernelUtil.h"

template <typename T>
Container<T>::~Container() {
    delete _ptr;
}

template <typename T>
Container<T>::Container() {
    _ptr = new T[1];
    _size = 1;
}

template <typename T>
Container<T>::Container(size_t size) {
    _ptr = new T[size];
    _size = size;
}

template <typename T>
Container<T>::Container(const T *data) {
    _size = 0;
    *this = data;
}

template <typename T>
Container<T> Container<T>::UseExisting(T *ptr) {
    Container toReturn;
    toReturn._ptr = ptr;
    return toReturn;
}

template<typename T>
Container<T> &Container<T>::operator=(const T *data) {
    delete _ptr;
    for (_size = 0; data[_size] != 0; _size++);
    _ptr = new T[_size];
    memcpy(_ptr, data, _size * sizeof(T));
    return *this;
}

template<typename T>
Container<T> &Container<T>::operator+=(const Container &other) {
    T *oldPtr = _ptr;
    _ptr = new T[other._size + _size];
    memcpy(_ptr, oldPtr, _size * sizeof(T));
    memcpy(_ptr + _size * sizeof(T), other._ptr, other._size * sizeof(T));
    delete oldPtr;
    return *this;
}

template<typename T>
Container<T> &Container<T>::operator+=(const T &item) {
    T *oldPtr = _ptr;
    _ptr = new T[++_size];
    memcpy(_ptr, oldPtr, _size * sizeof(T));
    _ptr[_size - 1] = item;
    delete oldPtr;
    return *this;
}

template<typename T>
Container<T> &Container<T>::operator+(const Container &other) {
    Container toReturn = *this;
    toReturn += other;
    return toReturn;
}

template<typename T>
Container<T> &Container<T>::operator+(const T &item) {
    Container toReturn = *this;
    toReturn += item;
    return toReturn;
}

template<typename T>
T &Container<T>::operator[](size_t index) {
    return _ptr[index];
}

template<typename T>
size_t Container<T>::Size() {
    return _size;
}
