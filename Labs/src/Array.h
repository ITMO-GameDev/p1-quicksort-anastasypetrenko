#pragma once

#include <cstring>
#include <cassert>

template <typename T>
class Array final {
public:
    class Iterator;

    Array();
    explicit Array(size_t capacity);

    Array<T>& operator=(const Array<T>& other) = delete;

    ~Array();

    void reserve(size_t size);

    void insert(const T& value);
    void insert(int index, const T& value);

    void remove(int index);

    const T& operator[](int index) const;
    T& operator[](int index);

    int size() const;

    const T* data() const;
    T* data();

    Iterator iterator();
    const Iterator iterator() const;

    class Iterator {
    public:
        friend class Array;

        const T& get() const;
        void set(const T& value);
        void insert(const T& value);
        void remove();
        void next();
        void prev();
        void toIndex(int index);
        bool hasNext() const;
        bool hasPrev() const;

    private:
        explicit Iterator(Array<T>* owner);
        Array<T>* mOwner;
        size_t mPos;
    };

private:
    size_t mCapacity;
    size_t mSize;
    T* mData;
};

template<typename T>
const T &Array<T>::Iterator::get() const {
    return (*mOwner)[mPos];
}

template<typename T>
void Array<T>::Iterator::set(const T &value) {
    (*mOwner)[mPos] = value;
}

template<typename T>
void Array<T>::Iterator::insert(const T &value) {
    mOwner->insert(mPos, value);
}

template<typename T>
void Array<T>::Iterator::remove() {
    mOwner->remove(mPos);
}

template<typename T>
void Array<T>::Iterator::next() {
    ++mPos;
    assert(mPos < mOwner->size());
}

template<typename T>
void Array<T>::Iterator::prev() {
    assert(mPos);
    --mPos;
}

template<typename T>
void Array<T>::Iterator::toIndex(int index) {
    assert(index < mOwner->size());
    mPos = index;
}

template<typename T>
bool Array<T>::Iterator::hasNext() const {
    return mPos + 1 < mOwner->size();
}

template<typename T>
bool Array<T>::Iterator::hasPrev() const {
    return mPos > 0;
}

template<typename T>
Array<T>::Iterator::Iterator(Array<T> *owner) : mOwner(owner), mPos(0) {

}

template<typename T>
Array<T>::Array() : Array(0) {

}

template<typename T>
Array<T>::Array(size_t capacity) : mData(nullptr), mCapacity(capacity), mSize(0) {
    if (mCapacity) {
        reserve(mCapacity);
    }
}

template<typename T>
Array<T>::~Array() {
    if (mData) {
        delete[](mData);
    }
}

template<typename T>
void Array<T>::insert(const T &value) {
    insert(mSize, value);
}

template<typename T>
void Array<T>::insert(int index, const T &value) {
    assert(index <= mSize);
    // can be optimized by copy not all data in reserve function
    reserve(mSize + 1);
//    size_t moveBytes = (size_ - index) * sizeof(T);
//    std::memmove(data_ + index + 1, data_ + index, moveBytes);
    for (size_t i = mSize; i > index; --i) {
        mData[i] = std::move(mData[i - 1]);
    }
    mData[index] = value;
    ++mSize;
}

template<typename T>
void Array<T>::remove(int index) {
    assert(index < mSize);
//    size_t moveBytes = (size_ - index- 1) * sizeof(T);
//    std::memmove(data_ + index, data_ + index + 1, moveBytes);
    for (size_t i = index; i < mSize + 1; ++i) {
        mData[i] = std::move(mData[i + 1]);
    }
    --mSize;
}

template<typename T>
const T &Array<T>::operator[](int index) const {
    return mData[index];
}

template<typename T>
T &Array<T>::operator[](int index) {
    return mData[index];
}

template<typename T>
int Array<T>::size() const {
    return mSize;
}

template<typename T>
void Array<T>::reserve(size_t size) {
    if (mCapacity < size) {
        size_t newCapacity = mCapacity == 0 ? 2 : mCapacity;
        while ((newCapacity <<= 1) < size);

        T* newData = new T[newCapacity];
        if (mCapacity) {
//            std::memcpy(newData, data_, capacity_ * sizeof(T));
            for (size_t i = 0; i < mSize; ++i) {
                newData[i] = std::move(mData[i + 1]);
            }
            delete[](mData);
        }

        mCapacity = newCapacity;
        mData = newData;
    }
}

template<typename T>
const T *Array<T>::data() const {
    return mData;
}

template<typename T>
T *Array<T>::data() {
    return mData;
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator() {
    return Array::Iterator(this);
}

template<typename T>
const typename Array<T>::Iterator Array<T>::iterator() const {
    return Array::Iterator(this);
}

