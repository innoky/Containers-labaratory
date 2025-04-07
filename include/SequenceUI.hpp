// include/SequenceUI.hpp
#pragma once

#include <iostream>
#include <limits>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void PrintSequence(const Sequence<T> &seq)
{
    for (int i = 0; i < seq.GetLength(); ++i)
        std::cout << seq.Get(i) << " ";
    std::cout << "\n";
}

template <typename T>
void SequenceUI(Sequence<T> *sequence)
{
    while (true)
    {
        std::cout << "\n=== MENU ===\n"
                  << "1. Append\n"
                  << "2. Prepend\n"
                  << "3. InsertAt\n"
                  << "4. Set\n"
                  << "5. Get\n"
                  << "6. GetSubSequence\n"
                  << "7. Concat\n"
                  << "8. Print\n"
                  << "9. Exit\n"
                  << "> ";

        int choice;
        std::cin >> choice;
        if (!std::cin)
        {
            ClearInput();
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 9)
            break;

        int index;
        T value;

        switch (choice)
        {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> value;
            sequence->Append(value);
            break;
        case 2:
            std::cout << "Enter value: ";
            std::cin >> value;
            sequence->Prepend(value);
            break;
        case 3:
            std::cout << "Enter index and value: ";
            std::cin >> index >> value;
            sequence->InsertAt(index, value);
            break;
        case 4:
            std::cout << "Enter index and value: ";
            std::cin >> index >> value;
            sequence->Set(index, value);
            break;
        case 5:
            std::cout << "Enter index: ";
            std::cin >> index;
            std::cout << "Value: " << sequence->Get(index) << "\n";
            break;
        case 6:
        {
            int start, end;
            std::cout << "Enter start and end: ";
            std::cin >> start >> end;
            Sequence<T> *sub = sequence->GetSubSequence(start, end);
            std::cout << "SubSequence: ";
            PrintSequence(*sub);
            delete sub;
            break;
        }
        case 7:
        {
            int count;
            std::cout << "Enter count of values to append: ";
            std::cin >> count;
            T *values = new T[count];
            std::cout << "Enter values: ";
            for (int i = 0; i < count; ++i)
                std::cin >> values[i];

            ArraySequence<T> temp(values, count);
            Sequence<T> *concat = sequence->Concat(temp);
            std::cout << "Result: ";
            PrintSequence(*concat);
            delete concat;
            delete[] values;
            break;
        }
        case 8:
            PrintSequence(*sequence);
            break;
        default:
            std::cout << "Unknown option.\n";
        }
    }
}
