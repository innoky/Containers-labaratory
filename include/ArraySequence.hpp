#pragma once

#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> array;

public:
    ArraySequence() = default;

    ArraySequence(T *items, int count) : array(items, count) {}

    ArraySequence(const DynamicArray<T> &otherArray) : array(otherArray) {}

    ArraySequence(const ArraySequence<T> &other) : array(other.array) {}

    T GetFirst() const override { return array.Get(0); }

    T GetLast() const override { return array.Get(array.GetSize() - 1); }

    T Get(int index) const override { return array.Get(index); }

    void Set(int index, const T &value) override { array.Set(index, value); }

    int GetLength() const override { return array.GetSize(); }

    void Append(const T &value) override { array.Append(value); }

    void Prepend(const T &value) override { array.Prepend(value); }

    void InsertAt(int index, const T &value) override { array.InsertAt(index, value); }

    Sequence<T> *SetAt(int index, const T &value) const override
    {
        return new ArraySequence<T>(array.SetAt(index, value));
    }

    Sequence<T> *Appended(const T &value) const override
    {
        return new ArraySequence<T>(array.Appended(value));
    }

    Sequence<T> *Prepended(const T &value) const override
    {
        return new ArraySequence<T>(array.Prepended(value));
    }

    Sequence<T> *InsertedAt(int index, const T &value) const override
    {
        return new ArraySequence<T>(array.InsertedAt(index, value));
    }
    
    Sequence<T> *GetSubSequence(int start, int end) const override
    {
        DynamicArray<T> sub = array.GetSubArray(start, end);
        return new ArraySequence<T>(sub);
    }

    Sequence<T> *Concat(const Sequence<T> &other) const override
    {
        auto *result = new ArraySequence<T>(*this);
        for (int i = 0; i < other.GetLength(); ++i)
            result->Append(other.Get(i));
        return result;
    }
};
