#pragma once

#include <memory>

template<class T>
class DynamicArray
{
private:
    std::unique_ptr<T[]> data;
    int size;

public:
    DynamicArray();
    DynamicArray(T *items, int count);      
    DynamicArray(int size);                    
    DynamicArray(const DynamicArray<T> &other);

    T Get(int index) const;
    int GetSize() const;
    void Set(int index, T value);
    void Resize(int newSize);
    void InsertAt(int index, const T &value);
    void Append(const T &value);
    void Prepend(const T &value);

    DynamicArray<T> SetAt(int index, const T &value) const;
    DynamicArray<T> Appended(const T &value) const;
    DynamicArray<T> Prepended(const T &value) const;
    DynamicArray<T> InsertedAt(int index, const T &value) const;

    DynamicArray<T> GetSubArray(int start, int end) const;
    DynamicArray<T> Concat(const DynamicArray<T> &other) const;

    T &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
};

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

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
int DynamicArray<T>::GetSize() const
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

template <class T>
void DynamicArray<T>::Append(const T &value)
{
    Resize(size + 1);
    data[size - 1] = value;
}

template <class T>
void DynamicArray<T>::Prepend(const T &value)
{
    Resize(size + 1);
    for (int i = size - 1; i > 0; --i)
        data[i] = data[i - 1];
    data[0] = value;
}

template <class T>
void DynamicArray<T>::InsertAt(int index, const T &value)
{
    if (index < 0 || index > size)
        throw std::out_of_range("Index out of range");

    Resize(size + 1);
    for (int i = size - 1; i > index; --i)
        data[i] = data[i - 1];
    data[index] = value;
}

template <class T>
DynamicArray<T> DynamicArray<T>::GetSubArray(int start, int end) const
{
    if (start < 0 || end > size || start > end)
        throw std::out_of_range("Invalid range");

    DynamicArray<T> result(end - start);
    for (int i = start; i < end; ++i)
        result.Set(i - start, data[i]);

    return result;
}

template <class T>
DynamicArray<T> DynamicArray<T>::Concat(const DynamicArray<T> &other) const
{
    DynamicArray<T> result(size + other.size);
    for (int i = 0; i < size; ++i)
        result.Set(i, data[i]);
    for (int i = 0; i < other.size; ++i)
        result.Set(size + i, other.data[i]);

    return result;
}

template <class T>
DynamicArray<T> DynamicArray<T>::SetAt(int index, const T &value) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    DynamicArray<T> result(*this); 
    result.Set(index, value);      
    return result;                 
}

template <class T>
DynamicArray<T> DynamicArray<T>::Appended(const T &value) const
{
    DynamicArray<T> result(*this);
    result.Append(value);
    return result;
}

template <class T>
DynamicArray<T> DynamicArray<T>::Prepended(const T &value) const
{
    DynamicArray<T> result(*this);
    result.Prepend(value);
    return result;
}

template <class T>
DynamicArray<T> DynamicArray<T>::InsertedAt(int index, const T &value) const
{
    DynamicArray<T> result(*this);
    result.InsertAt(index, value);
    return result;
}
