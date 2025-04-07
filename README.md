# Containers Labaratory

![MEPhI Logo](https://nvpk-mephi.ru/wp-content/uploads/2021/09/3ddda32c713589b65cd686fddb280b3f.png)

**Containers Labaratory** — это C++ библиотека, разработанная в рамках лабораторной работы по курсу *"Полиморфные и абстрактные типы данных"*. Она реализует абстрактный тип данных **последовательность** двумя способами:
- с использованием **динамического массива**,
- с использованием **связного списка**.

Также присутствуют **изменяемые (mutable)** и **неизменяемые (immutable)** версии последовательностей.

Внутренняя часть работает преимущественно на умных указателях

---

## 📁 Содержание

- [Установка](#установка)
- [Использование](#использование)
- [Интерфейс Sequence](#интерфейс-sequence)
- [Типы последовательностей](#типы-последовательностей)
- [Примеры](#примеры)
- [Тесты](#тесты)
- [Сборка](#сборка)
- [Лицензия](#лицензия)

---

## 📦 Установка

```bash
git clone https://github.com/yourusername/SequenceLab.git
cd SequenceLab
mkdir build && cd build
cmake ..
make
```

---

## 🚀 Использование

Подключите нужную реализацию:

```cpp
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
```

Создайте объект:
```cpp
int data[] = {1, 2, 3};
ArraySequence<int> seq(data, 3);
```

---

## 📐 Интерфейс `Sequence`

```cpp
template <class T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual void Set(int index, const T& value) = 0;
    virtual int GetLength() const = 0;

    virtual void Append(const T& value) = 0;
    virtual void Prepend(const T& value) = 0;
    virtual void InsertAt(int index, const T& value) = 0;

    virtual Sequence<T>* GetSubSequence(int start, int end) const = 0;
    virtual Sequence<T>* Concat(const Sequence<T>& other) const = 0;

    virtual ~Sequence() = default;
};
```

---

## 🧩 Типы последовательностей

- `ArraySequence<T>` — на базе `DynamicArray`
- `ListSequence<T>` — на базе `LinkedList`
- `ImmutableArraySequence<T>` — только чтение
- `ImmutableListSequence<T>` — только чтение

---

## 🧪 Тесты

Для библиотеки реализованы юнит-тесты с использованием **Catch2**:

- `test_array.cpp` — тесты `ArraySequence`
- `test_list.cpp` — тесты `ListSequence`
- `test_immutable_array.cpp` — тесты `ImmutableArraySequence`
- `test_immutable_list.cpp` — тесты `ImmutableListSequence`

Запуск тестов:
```bash
make tests
./tests

make immutable_tests
./immutable_tests
```

---

## 🔧 Сборка

```bash
mkdir build
cd build
cmake ..
make
```

Сборка `main`:
```bash
./lab2
```

---

## ⚖️ Лицензия

MIT License.
