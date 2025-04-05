#pragma once

#include <memory>

template<typename T>
class DynamicArray
{
private:
    std::unique_ptr<T[]> data;
    int size;

public:
    DynamicArray(T *items, int count);      
    DynamicArray(int size);                    
    DynamicArray(const DynamicArray<T> &other); 

    T Get(int index) const;
    void Set(int index, T value);
    void Resize(int newSize);
};

template <typename T>
DynamicArray<T>::DynamicArray(T *items, int count)
{
    data = std::make_unique<T[]>(count);
    this->size = count;
    for (int i = 0; i < count; i++)
        data[i] = items[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(int size)
{
    data = std::make_unique<T[]>(size);
    this->size = size;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
{
    size = other.size;
    data = std::make_unique<T[]>(size);
    for (int i = 0; i < size; i++)
        data[i] =other.data[i];
}

template <typename T>
T DynamicArray<T>::Get(int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}