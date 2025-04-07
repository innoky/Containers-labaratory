#pragma once

template <class T>
class ImmutableSequence
{
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    // Mutable operations
    virtual ImmutableSequence<T> *SetAt(int index, const T &value) const = 0;
    virtual ImmutableSequence<T> *Appended(const T &value) const = 0;
    virtual ImmutableSequence<T> *Prepended(const T &value) const = 0;
    virtual ImmutableSequence<T> *InsertedAt(int index, const T &value) const = 0;

    virtual ImmutableSequence<T> *GetSubSequence(int start, int end) const = 0;
    virtual ImmutableSequence<T> *Concat(const ImmutableSequence<T> &other) const = 0;

    virtual ~ImmutableSequence() = default;
};
