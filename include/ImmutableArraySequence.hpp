#pragma once

#include "ImmutableSequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ImmutableArraySequence : public ImmutableSequence<T>
{
private:
    DynamicArray<T> array;

public:
    ImmutableArraySequence() = default;

    ImmutableArraySequence(const DynamicArray<T> &source) : array(source) {}

    ImmutableArraySequence(T *items, int count) : array(items, count) {}

    ImmutableArraySequence(const ImmutableArraySequence<T> &other) : array(other.array) {}

    T GetFirst() const override { return array.Get(0); }

    T GetLast() const override { return array.Get(array.GetSize() - 1); }

    T Get(int index) const override { return array.Get(index); }

    int GetLength() const override { return array.GetSize(); }

    ImmutableSequence<T> *SetAt(int index, const T &value) const override
    {
        DynamicArray<T> result = array.SetAt(index, value);
        return new ImmutableArraySequence<T>(result);
    }

    ImmutableSequence<T> *Appended(const T &value) const override
    {
        DynamicArray<T> result = array.Appended(value);
        return new ImmutableArraySequence<T>(result);
    }

    ImmutableSequence<T> *Prepended(const T &value) const override
    {
        DynamicArray<T> result = array.Prepended(value);
        return new ImmutableArraySequence<T>(result);
    }

    ImmutableSequence<T> *InsertedAt(int index, const T &value) const override
    {
        DynamicArray<T> result = array.InsertedAt(index, value);
        return new ImmutableArraySequence<T>(result);
    }

    ImmutableSequence<T> *GetSubSequence(int start, int end) const override
    {
        DynamicArray<T> sub = array.GetSubArray(start, end);
        return new ImmutableArraySequence<T>(sub);
    }

    ImmutableSequence<T> *Concat(const ImmutableSequence<T> &other) const override
    {
        const auto &casted = dynamic_cast<const ImmutableArraySequence<T> &>(other);
        DynamicArray<T> merged = array.Concat(casted.array);
        return new ImmutableArraySequence<T>(merged);
    }
};
