
# Containers Labaratory

![MEPhI Logo](https://nvpk-mephi.ru/wp-content/uploads/2021/09/3ddda32c713589b65cd686fddb280b3f.png)

**Containers Labaratory** — это C++ библиотека, разработанная в рамках лабораторной работы по курсу *"Полиморфные и абстрактные типы данных"*. Она реализует абстрактный тип данных **последовательность** двумя способами:
- с использованием **динамического массива** (`Array`),
- с использованием **связного списка** (`List`).

Также поддерживаются **изменяемые (mutable)** и **неизменяемые (immutable)** версии контейнеров. Все типы используют умные указатели (`std::unique_ptr`) для управления памятью.

---

## 📁 Содержание

- [Установка](#установка)
- [Использование](#использование)
- [Интерфейс Sequence](#интерфейс-sequence)
- [Типы последовательностей](#типы-последовательностей)
- [UI](#ui)
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

Подключите нужные реализации:

```cpp
#include "ArrayMutableSequence.hpp"
#include "ListImmutableSequence.hpp"
```

Пример:

```cpp
ArrayMutableSequence<int> seq;
seq.AppendInPlace(10);
seq.AppendInPlace(20);
std::cout << seq.GetFirst();  // 10
```

Для `Immutable` последовательностей:

```cpp
int data[] = {1, 2, 3};
ArrayImmutableSequence<int> seq(data, 3);
auto newSeq = seq.Append(4);
```

---

## 📐 Интерфейс `ISequence`

```cpp
template <typename T>
class ISequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) const = 0;

    virtual ~ISequence() = default;
};
```

---

## 🧩 Типы последовательностей

### 🛠 Mutable:
- `ArrayMutableSequence<T>` — изменяемая, на базе `DynamicArray`
- `ListMutableSequence<T>` — изменяемая, на базе `LinkedList`

### 🔒 Immutable:
- `ArrayImmutableSequence<T>` — неизменяемая, массивная
- `ListImmutableSequence<T>` — неизменяемая, списковая

---

## 🖥 UI

Пример запуска интерфейса пользователя (CLI):

```bash
./SeqUI
```

Доступно меню с выбором типа последовательности и базовыми действиями (добавление, просмотр и операции с контейнером).

---

## 🧪 Тесты

Для библиотеки реализованы юнит-тесты:

- `SequenceTest` — полный набор тестов для всех типов последовательностей

Запуск:

```bash
make
./SequenceTest
```

---

## 🔧 Сборка

```bash
mkdir build
cd build
cmake ..
make
```

Запуск тестов:

```bash
./SequenceTest
```

Запуск пользовательского интерфейса:

```bash
./SeqUI
```

---

## ⚖️ Лицензия

MIT License.
