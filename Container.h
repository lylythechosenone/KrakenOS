#ifndef KRAKENOS_CONTAINER_H
#define KRAKENOS_CONTAINER_H

#include <KernelTypes.h>

template <typename T>
class Container {
public:
    ~Container();
    Container();

    Container(size_t size);
    Container(const T *data);

    /**
     * @warning DO NOT use this with a temporary pointer. \n
     * This method is for temporarily using an existing pointer rather than creating a new one.
     */
    static Container UseExisting(T *ptr);

    Container<T> &operator=(const T *data);

    Container<T> &operator+(const Container &other);
    Container<T> &operator+(const T &item);
    Container<T> &operator+=(const Container &other);
    Container<T> &operator+=(const T &item);

    T &operator[](size_t index);

    size_t Size();
    size_t (*Length)() = Size;

private:
    T *_ptr;
    size_t _size;
};

#endif //KRAKENOS_CONTAINER_H
