#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

int main()
{
    Sequence<int> *arrSeq = new ArraySequence<int>();
    Sequence<int> *listSeq = new ListSequence<int>();

    for (int i = 1; i <= 5; ++i)
    {
        arrSeq->Append(i * 10);
        listSeq->Prepend(i);
    }

    std::cout << "ArraySequence: ";
    for (int i = 0; i < arrSeq->GetLength(); ++i)
        std::cout << arrSeq->Get(i) << " ";
    std::cout << "\n";

    std::cout << "ListSequence: ";
    for (int i = 0; i < listSeq->GetLength(); ++i)
        std::cout << listSeq->Get(i) << " ";
    std::cout << "\n";

    delete arrSeq;
    delete listSeq;
}
