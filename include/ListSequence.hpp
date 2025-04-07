#pragma once

#include "Sequence.hpp"
#include "LinkedList.hpp"

template <class T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;

public:
    ListSequence() = default;
    ListSequence(T *items, int count) : list(items, count) {}
    ListSequence(const LinkedList<T> &otherList) : list(otherList) {}
    ListSequence(const ListSequence<T> &other) : list(other.list) {}


    T GetFirst() const override { return list.GetFirst(); }

    T GetLast() const override { return list.GetLast(); }

    T Get(int index) const override { return list.Get(index); }
    
    int GetLength() const override { return list.GetSize(); }

    T &operator[](int index) { return list[index]; }

    void Set(int index, const T &value) override { list.Set(index, value); }

    void InsertAt(int index, const T &value) override
    {
        list.InsertAt(index, value);
    }

   

    void Append(const T &value) override { list.Append(value); }

    void Prepend(const T &value) override { list.Prepend(value); }

    Sequence<T> *GetSubSequence(int start, int end) const override
    {
        LinkedList<T> *sub = list.GetSubList(start, end);
        return new ListSequence<T>(*sub);
    }

    Sequence<T> *Concat(const Sequence<T> &other) const override
    {
        auto *result = new ListSequence<T>(*this); // копируем текущее
        for (int i = 0; i < other.GetLength(); ++i)
            result->Append(other.Get(i));
        return result;
    }
};
