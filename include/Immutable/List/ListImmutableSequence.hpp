#pragma once

#include "include/Immutable/ImmutableSequence.hpp"
#include "include/core/LinkedList.hpp"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <utility>

template <typename T>
class ListImmutableSequence : public ImmutableSequence<T>
{
private:
    LinkedList<T> data;

public:
    ListImmutableSequence() = default;

    ListImmutableSequence(const T *items, int count) : data(items, count) {}

    T GetFirst() const override
    {
        if (data.GetLength() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.GetFirst();
    }

    T GetLast() const override
    {
        if (data.GetLength() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.GetLast();
    }

    T Get(int index) const override
    {
        return data.Get(index);
    }

    int GetLength() const override
    {
        return data.GetLength();
    }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
            throw std::out_of_range("Invalid indices for subsequence");
        LinkedList<T> *subList = data.GetSubList(startIndex, endIndex);
        auto newSeq = std::make_unique<ListImmutableSequence<T>>();
        newSeq->data = *subList;
        delete subList;
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto newSeq = std::make_unique<ListImmutableSequence<T>>(*this);
        newSeq->data.Append(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto newSeq = std::make_unique<ListImmutableSequence<T>>(*this);
        newSeq->data.Prepend(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        if (index < 0 || index > GetLength())
            throw std::out_of_range("Invalid index for insert");
        auto newSeq = std::make_unique<ListImmutableSequence<T>>(*this);
        newSeq->data.InsertAt(item, index);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto newSeq = std::make_unique<ListImmutableSequence<T>>(*this);
        for (int i = 0; i < list->GetLength(); ++i)
        {
            newSeq->data.Append(list->Get(i));
        }
        return newSeq;
    }

    std::unique_ptr<ListImmutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
        auto newSeq = std::make_unique<ListImmutableSequence<T>>();
        for (int i = 0; i < data.GetLength(); ++i)
        {
            newSeq->data.Append(func(data.Get(i)));
        }
        return newSeq;
    }

    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (int i = 0; i < data.GetLength(); ++i)
        {
            accumulator = func(accumulator, data.Get(i));
        }
        return accumulator;
    }

    std::unique_ptr<ListImmutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        auto newSeq = std::make_unique<ListImmutableSequence<T>>();
        for (int i = 0; i < data.GetLength(); ++i)
        {
            if (predicate(data.Get(i)))
            {
                newSeq->data.Append(data.Get(i));
            }
        }
        return newSeq;
    }

    template <typename U>
    std::unique_ptr<ListImmutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        auto newSeq = std::make_unique<ListImmutableSequence<std::pair<T, U>>>();
        int minLength = std::min(this->GetLength(), other->GetLength());
        for (int i = 0; i < minLength; ++i)
        {
            newSeq->Append({this->Get(i), other->Get(i)});
        
        }
        return newSeq;
    }
};
