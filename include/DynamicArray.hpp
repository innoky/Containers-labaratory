#pragma once

#include <memory>

template<class T>
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
    int GetSize();
    void Set(int index, T value);
    void Resize(int newSize);
};

template <class T>
DynamicArray<T>::DynamicArray(T *items, int count)
{
    data = std::make_unique<T[]>(count);
    this->size = count;
    for (int i = 0; i < count; i++)
        data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(int size)
{
    data = std::make_unique<T[]>(size);
    this->size = size;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
{
    size = other.size;
    data = std::make_unique<T[]>(size);
    for (int i = 0; i < size; i++)
        data[i] =other.data[i];
}

template <class T>
T DynamicArray<T>::Get(int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <class T>
int DynamicArray<T>::GetSize()
{
    return size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newSize)
{
    std::unique_ptr<T[]> tmp_data = std::make_unique<T[]>(newSize);
    int copySize = ( newSize < size ) ? newSize : size;

    for (int i = 0; i < copySize; ++i)
        tmp_data[i] = data[i];

    data = std::move(tmp_data); 
    size = newSize;
}