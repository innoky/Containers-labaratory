#pragma once

template <class T>
class Sequence
{
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    // Mutable operations
    virtual void Set(int index, const T &value) = 0;
    virtual void Append(const T &value) = 0;
    virtual void Prepend(const T &value) = 0;
    virtual void InsertAt(int index, const T &value) = 0;

    // Immutable versions
    virtual Sequence<T> *SetAt(int index, const T &value) const = 0;
    virtual Sequence<T> *Appended(const T &value) const = 0;
    virtual Sequence<T> *Prepended(const T &value) const = 0;
    virtual Sequence<T> *InsertedAt(int index, const T &value) const = 0;

    
    virtual Sequence<T> *GetSubSequence(int start, int end) const = 0;
    virtual Sequence<T> *Concat(const Sequence<T> &other) const = 0;

    virtual ~Sequence() = default;
};
