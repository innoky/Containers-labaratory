#pragma once

#include "ImmutableSequence.hpp"
#include "LinkedList.hpp"

template <class T>
class ImmutableListSequence : public ImmutableSequence<T>
{
private:
    LinkedList<T> list;

public:
    ImmutableListSequence() = default;

    ImmutableListSequence(const LinkedList<T> &src) : list(src) {}

    ImmutableListSequence(T *items, int count) : list(items, count) {}

    T GetFirst() const override { return list.GetFirst(); }
    T GetLast() const override { return list.GetLast(); }
    T Get(int index) const override { return list.Get(index); }
    int GetLength() const override { return list.GetSize(); }

    ImmutableSequence<T> *SetAt(int index, const T &value) const override
    {
        LinkedList<T> result = list.SetAt(index, value);
        return new ImmutableListSequence<T>(result);
    }

    ImmutableSequence<T> *Appended(const T &value) const override
    {
        LinkedList<T> result = list.Appended(value);
        return new ImmutableListSequence<T>(result);
    }

    ImmutableSequence<T> *Prepended(const T &value) const override
    {
        LinkedList<T> result = list.Prepended(value);
        return new ImmutableListSequence<T>(result);
    }

    ImmutableSequence<T> *InsertedAt(int index, const T &value) const override
    {
        LinkedList<T> result = list.InsertedAt(index, value);
        return new ImmutableListSequence<T>(result);
    }

    ImmutableSequence<T> *GetSubSequence(int start, int end) const override
    {
        LinkedList<T> *sub = list.GetSubList(start, end);
        return new ImmutableListSequence<T>(*sub);
    }

    ImmutableSequence<T> *Concat(const ImmutableSequence<T> &other) const override
    {
        const auto &casted = dynamic_cast<const ImmutableListSequence<T> &>(other);
        LinkedList<T> *result = list.Concat(casted.list);
        return new ImmutableListSequence<T>(*result);
    }
};
