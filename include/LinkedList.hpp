#pragma once

#include <memory>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        Node(const T &val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    Node *tail;
    
    int size;

public:
    //////////// ITERATORS ////////////
    
    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        T &operator*() const
        {
            return current->data;
        }

        Iterator &operator++()
        {
            current = current->next.get();
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin()
    {
        return Iterator(head.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    class ConstIterator
    {
    private:
        const Node *current;

    public:
        ConstIterator(const Node *node) : current(node) {}

        const T &operator*() const { return current->data; }

        ConstIterator &operator++()
        {
            current = current->next.get();
            return *this;
        }

        bool operator!=(const ConstIterator &other) const
        {
            return current != other.current;
        }
    };

    ConstIterator begin() const
    {
        return ConstIterator(head.get());
    }

    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    ////////////////////////////////////

    LinkedList();
    LinkedList(T *items, int count);
    LinkedList(const LinkedList<T> &other);

    T &operator[](int index);
    const T &operator[](int index) const;
    LinkedList<T> &operator=(const LinkedList<T> &other);

    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    T& GetLink(int index);

    int GetSize() const;

    void Append(const T &item);
    void Prepend(const T &item);
    void InsertAt(int index, const T &item);
    void Set(int index, const T &item);

    LinkedList<T> *GetSubList(int start, int end) const;
    LinkedList<T> *Concat(const LinkedList<T> &other) const;

    //Immutable methods

    LinkedList<T> SetAt(int index, const T &value) const;
    LinkedList<T> Appended(const T &value) const;
    LinkedList<T> Prepended(const T &value) const;
    LinkedList<T> InsertedAt(int index, const T &value) const;
};

template <class T>
LinkedList<T>::LinkedList(): head(nullptr), tail(nullptr), size(0){}

template <class T>
void LinkedList<T>::Append(const T &item)
{
    auto newNode = std::make_unique<Node>(item);
    Node *rawPtr = newNode.get();

    if (!head)
    {
        head = std::move(newNode);
        tail = rawPtr;
    }
    else
    {
        tail->next = std::move(newNode);
        tail = rawPtr;
    }
    size++;
}

template <class T>
void LinkedList<T>::Prepend(const T &item)
{
    auto newNode = std::make_unique<Node>(item);
    Node *rawPtr = newNode.get();

    if (!head)
    {
        head = std::move(newNode);
        tail = rawPtr;
    }
    else
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    size++;
}

template <class T>
T LinkedList<T>::GetFirst() const
{
    if (!head)
    {
        throw std::out_of_range("Index out of range");
    }
    return head->data;
}

template <class T>
T LinkedList<T>::GetLast() const
{
    if (!tail)
    {
        throw std::out_of_range("Index out of range");
    }
    return tail->data;
}

template <class T>
int LinkedList<T>::GetSize() const
{
    return size;
}

template <class T>
T LinkedList<T>::Get(int index) const 
{
    if (!head || index < 0) 
        throw std::out_of_range("Index out of range");

    int iterator = 0;
    Node *c = head.get();
    while(iterator < index)
    {
        if (c->next == nullptr)
            throw std::out_of_range("Index out of range");
        c = c->next.get();
        iterator++;
    }
    return c->data;
}

template <class T>
T& LinkedList<T>::GetLink(int index)
{
    if (!head || index < 0)
        throw std::out_of_range("Index out of range");

    int iterator = 0;
    Node *c = head.get();
    while (iterator < index)
    {
        if (c->next == nullptr)
            throw std::out_of_range("Index out of range");
        c = c->next.get();
        iterator++;
    }
    return c->data;
}

template <class T>
void LinkedList<T>::Set(int index, const T &item)
{
    if (!head || index < 0)
        throw std::out_of_range("Index out of range");

    int iterator = 0;
    Node *c = head.get();
    while (iterator < index)
    {
        if (c->next == nullptr)
            throw std::out_of_range("Index out of range");
        c = c->next.get();
        iterator++;
    }
    c->data = item;
}

template <class T>
void LinkedList<T>::InsertAt(int index, const T &item)
{
    if (index < 0)
        throw std::out_of_range("Index out of range");

    if (index == size)
    {
        Append(item);
        return;
    }

    int iterator = 0;
    Node *c = head.get();
    Node *prev;
    while (iterator < index)
    {
        if (c->next == nullptr)
            throw std::out_of_range("Index out of range");
        prev = c;
        c = c->next.get();
        iterator++;
    }

    auto newNode = std::make_unique<Node>(item);

    if (index == 0)
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (size == 0) tail = head.get();
    }
    else
    {
        newNode->next = std::move(prev->next);
        prev->next = std::move(newNode);
    }

    size++;
}

template <class T>
LinkedList<T>::LinkedList(T *items, int count)

{

    auto headNode = std::make_unique<Node>(items[0]);
    head = std::move(headNode);
    auto prev = head.get();
    for (int i = 1; i < count; ++i)
    {
        auto newNode = std::make_unique<Node>(items[i]);
        prev->next = std::move(newNode);
        prev = prev->next.get();
    }
    tail = prev;
    size = count;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
    if (other.GetSize() == 0)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    else
    {
        auto headNode = std::make_unique<Node>(other.Get(0));
        head = std::move(headNode);
        auto prev = head.get();
        for (int i = 1; i < other.GetSize(); ++i)
        {
            auto newNode = std::make_unique<Node>(other.Get(i));
            prev->next = std::move(newNode);
            prev = prev->next.get();
        }
        tail = prev;
        size = other.GetSize();
    }
}

template <class T>
T &LinkedList<T>::operator[](int index)
{
    return GetLink(index);
}

template <class T>
const T &LinkedList<T>::operator[](int index) const
{
    if (!head || index < 0)
        throw std::out_of_range("Index out of range");

    int iterator = 0;
    Node *c = head.get();
    while (iterator < index)
    {
        if (!c->next)
            throw std::out_of_range("Index out of range");
        c = c->next.get();
        iterator++;
    }

    return c->data;
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
        return *this; 

    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;

    if (other.GetSize() == 0)
        return *this;

    this->head = std::make_unique<Node>(other[0]);
    Node *prev = this->head.get();

    for (int i = 1; i < other.GetSize(); ++i)
    {
        auto newNode = std::make_unique<Node>(other[i]);
        prev->next = std::move(newNode);
        prev = prev->next.get();
    }

    this->tail = prev;
    this->size = other.GetSize();

    return *this;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int start, int end) const
{
    if (start < 0 || end > size || start > end)
        throw std::out_of_range("Borders out of range");

    LinkedList* newLinkedList = new LinkedList();
    for (int i = start; i < end; ++i)
    {
        (*newLinkedList).Append((*this)[i]);
    }
    return newLinkedList;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T> &other) const
{
    LinkedList *newLinkedList = new LinkedList(*this);

    for(int i = 0; i < other.GetSize(); i++)
    {
        newLinkedList->Append(other[i]);
    }

    return newLinkedList;
}

template <class T>
LinkedList<T> operator+(const LinkedList<T> &lhs, const LinkedList<T> &rhs)
{
    std::unique_ptr<LinkedList<T>> result(lhs.Concat(rhs));
    return *result;
}

template <class T>
LinkedList<T> LinkedList<T>::SetAt(int index, const T &value) const
{
    LinkedList<T> result(*this);
    result.Set(index, value);
    return result;
}

template <class T>
LinkedList<T> LinkedList<T>::Appended(const T &value) const
{
    LinkedList<T> result(*this);
    result.Append(value);
    return result;
}

template <class T>
LinkedList<T> LinkedList<T>::Prepended(const T &value) const
{
    LinkedList<T> result(*this);
    result.Prepend(value);
    return result;
}

template <class T>
LinkedList<T> LinkedList<T>::InsertedAt(int index, const T &value) const
{
    LinkedList<T> result(*this);
    result.InsertAt(index, value);
    return result;
}
