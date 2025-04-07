#include <iostream>
#include "../include/ArraySequence.hpp"
#include "../include/ListSequence.hpp"
#include "SequenceUI.hpp"

int main()
{
    std::cout << "Choose structure:\n1. ArraySequence\n2. ListSequence\n> ";
    int choice;
    std::cin >> choice;

    Sequence<int> *seq = nullptr;
    if (choice == 1)
        seq = new ArraySequence<int>();
    else if (choice == 2)
        seq = new ListSequence<int>();
    else
    {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    SequenceUI(seq);
    delete seq;

    return 0;
}
