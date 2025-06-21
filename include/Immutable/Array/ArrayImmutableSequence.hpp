#pragma once

#include "include/Immutable/ImmutableSequence.hpp"
#include "include/core/DynamicArray.hpp"
#include <memory>
#include <functional>
#include <utility>
#include <stdexcept>

template <typename T>
class ArrayImmutableSequence : public ImmutableSequence<T>
{
private:
    DynamicArray<T> data;

public:
    ArrayImmutableSequence(const T *items, int count)
        : data(items, count)
    {
    }

    T GetFirst() const override
    {
        if (data.GetSize() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.Get(0);
    }

    T GetLast() const override
    {
        if (data.GetSize() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.Get(data.GetSize() - 1);
    }

    T Get(int index) const override
    {
        return data.Get(index);
    }

    int GetLength() const override
    {
        return data.GetSize();
    }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
            throw std::out_of_range("Invalid indices for subsequence");
        int newSize = endIndex - startIndex + 1;
        T *subItems = new T[newSize];
        for (int i = 0; i < newSize; ++i)
        {
            subItems[i] = data.Get(startIndex + i);
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(subItems, newSize);
        delete[] subItems;
        return result;
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        int oldSize = data.GetSize();
        int newSize = oldSize + 1;
        T *newItems = new T[newSize];
        for (int i = 0; i < oldSize; ++i)
        {
            newItems[i] = data.Get(i);
        }
        newItems[oldSize] = item;
        auto result = std::make_unique<ArrayImmutableSequence<T>>(newItems, newSize);
        delete[] newItems;
        return result;
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        int oldSize = data.GetSize();
        int newSize = oldSize + 1;
        T *newItems = new T[newSize];
        newItems[0] = item;
        for (int i = 0; i < oldSize; ++i)
        {
            newItems[i + 1] = data.Get(i);
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(newItems, newSize);
        delete[] newItems;
        return result;
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        if (index < 0 || index > data.GetSize())
            throw std::out_of_range("Index out of bounds");
        int oldSize = data.GetSize();
        int newSize = oldSize + 1;
        T *newItems = new T[newSize];
        for (int i = 0; i < index; ++i)
        {
            newItems[i] = data.Get(i);
        }
        newItems[index] = item;
        for (int i = index; i < oldSize; ++i)
        {
            newItems[i + 1] = data.Get(i);
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(newItems, newSize);
        delete[] newItems;
        return result;
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        int ourSize = data.GetSize();
        int theirSize = list->GetLength();
        int newSize = ourSize + theirSize;
        T *newItems = new T[newSize];
        for (int i = 0; i < ourSize; ++i)
        {
            newItems[i] = data.Get(i);
        }
        for (int i = 0; i < theirSize; ++i)
        {
            newItems[ourSize + i] = list->Get(i);
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(newItems, newSize);
        delete[] newItems;
        return result;
    }

    std::unique_ptr<ArrayImmutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
        int size = data.GetSize();
        T *mappedItems = new T[size];
        for (int i = 0; i < size; ++i)
        {
            mappedItems[i] = func(data.Get(i));
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(mappedItems, size);
        delete[] mappedItems;
        return result;
    }

    std::unique_ptr<ArrayImmutableSequence<T>> MapIndexed(std::function<T(const T &, int)> func) const
    {
        int size = data.GetSize();
        T *mappedItems = new T[size];
        for (int i = 0; i < size; ++i)
        {
            mappedItems[i] = func(data.Get(i), i);
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(mappedItems, size);
        delete[] mappedItems;
        return result;
    }

    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            accumulator = func(accumulator, data.Get(i));
        }
        return accumulator;
    }

    std::unique_ptr<ArrayImmutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        int newSize = 0;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            if (predicate(data.Get(i)))
            {
                newSize++;
            }
        }

        T *filteredItems = new T[newSize];
        int current = 0;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            if (predicate(data.Get(i)))
            {
                filteredItems[current++] = data.Get(i);
            }
        }
        auto result = std::make_unique<ArrayImmutableSequence<T>>(filteredItems, newSize);
        delete[] filteredItems;
        return result;
    }

    template <typename U>
    std::unique_ptr<ArrayImmutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        int minLength = std::min(data.GetSize(), other->GetLength());
        using ZippedType = std::pair<T, U>;
        ZippedType *zippedItems = new ZippedType[minLength];

        for (int i = 0; i < minLength; ++i)
        {
            zippedItems[i] = {data.Get(i), other->Get(i)};
        }
        auto result = std::make_unique<ArrayImmutableSequence<ZippedType>>(zippedItems, minLength);
        delete[] zippedItems;
        return result;
    }
};
