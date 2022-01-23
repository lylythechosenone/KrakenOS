#ifndef KRAKENOS_KERNELTYPES_H
#define KRAKENOS_KERNELTYPES_H

#include <stdint-gcc.h>

using UInt8 = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;

using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int64 = int64_t;

using Byte = UInt8;
using Word = UInt16;
using DWord = UInt32;
using QWord = UInt64;

using size_t = UInt64;

/*
template <typename T>
class Container {
public:
    Container();
    Container(const T*);
    Container(const Container<T>&);

    Container &operator=(const T*);

    T &operator[](size_t);

    size_t length() const;
private:
    T *_ptr;
    size_t _length;
};

template<typename T>
Container<T>::Container() {
    _ptr = nullptr;
    _length = 0;
}

template<typename T>
Container<T>::Container(const T *data) {
    *this = data;
}

template<typename T>
Container<T>::Container(const Container<T> &container) {
    *this = container;
}

template<typename T>
Container<T> &Container<T>::operator=(const T *data) {
    for (size_t i = 0; data[i] != '\0'; i++) {
        _length++;
    }
    _ptr = new T[_length];
    for (size_t i = 0; i < _length; i++) {
        _ptr[i] = data[i];
    }
}

template<typename T>
T &Container<T>::operator[](size_t index) {
    return _ptr[index];
}

template<typename T>
size_t Container<T>::length() const {
    return _length;
}

typedef Container<char> String;

template<typename T>
using Vector = Container<T>;
*/

#endif //KRAKENOS_KERNELTYPES_H
