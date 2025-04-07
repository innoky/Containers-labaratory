#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../include/ArraySequence.hpp"
#include "../include/ListSequence.hpp"
#include "../include/ImmutableArraySequence.hpp"
#include "../include/ImmutableListSequence.hpp"

TEST_CASE("Mutable ArraySequence", "[ArraySequence]")
{
    int data[] = {10, 20, 30};

    ArraySequence<int> seq(data, 3);
    REQUIRE(seq.GetFirst() == 10);
    REQUIRE(seq.GetLast() == 30);
    REQUIRE(seq[1] == 20);
    REQUIRE(seq.Get(1) == 20);
    REQUIRE(seq.GetLength() == 3);

    seq.Set(1, 99);
    REQUIRE(seq[1] == 99);

    seq.Append(40);
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.GetLast() == 40);

    seq.Prepend(5);
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetFirst() == 5);

    seq.InsertAt(2, 777);
    REQUIRE(seq[2] == 777);

    SECTION("SubSequence and Concat")
    {
        auto sub = seq.GetSubSequence(1, 4);
        REQUIRE(sub->GetLength() == 3);
        REQUIRE(sub->Get(0) == 10);
        delete sub;

        auto concat = seq.Concat(seq);
        REQUIRE(concat->GetLength() == 2 * seq.GetLength());
        REQUIRE(concat->Get(seq.GetLength()) == seq[0]);
        delete concat;
    }
}

TEST_CASE("Mutable ListSequence", "[ListSequence]")
{
    int data[] = {1, 2, 3, 4};
    ListSequence<int> list(data, 4);

    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.GetFirst() == 1);
    REQUIRE(list.GetLast() == 4);
    REQUIRE(list[2] == 3);

    list.Set(0, 100);
    REQUIRE(list[0] == 100);

    list.Append(5);
    REQUIRE(list.GetLast() == 5);

    list.Prepend(0);
    REQUIRE(list.GetFirst() == 0);

    list.InsertAt(2, 42);
    REQUIRE(list[2] == 42);

    auto sub = list.GetSubSequence(1, 3);
    REQUIRE(sub->GetLength() == 2);
    REQUIRE(sub->Get(1) == list[2]);
    delete sub;

    auto concat = list.Concat(list);
    REQUIRE(concat->GetLength() == 2 * list.GetLength());
    delete concat;
}

TEST_CASE("ImmutableArraySequence", "[ImmutableArray]")
{
    int data[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(data, 3);

    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.Get(1) == 2);

    auto modified = seq.SetAt(1, 99);
    REQUIRE(modified->Get(1) == 99);
    REQUIRE(seq.Get(1) == 2); // original is unchanged
    delete modified;

    auto appended = seq.Appended(4);
    REQUIRE(appended->GetLength() == 4);
    REQUIRE(appended->Get(3) == 4);
    delete appended;

    auto prepended = seq.Prepended(0);
    REQUIRE(prepended->Get(0) == 0);
    delete prepended;

    auto inserted = seq.InsertedAt(1, 88);
    REQUIRE(inserted->Get(1) == 88);
    delete inserted;
}

TEST_CASE("ImmutableListSequence", "[ImmutableList]")
{
    int data[] = {1, 2, 3};
    ImmutableListSequence<int> seq(data, 3);

    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(2) == 3);

    auto modified = seq.SetAt(2, 111);
    REQUIRE(modified->Get(2) == 111);
    REQUIRE(seq.Get(2) == 3);
    delete modified;

    auto appended = seq.Appended(42);
    REQUIRE(appended->GetLength() == 4);
    REQUIRE(appended->Get(3) == 42);
    delete appended;

    auto prepended = seq.Prepended(7);
    REQUIRE(prepended->Get(0) == 7);
    delete prepended;

    auto inserted = seq.InsertedAt(1, 99);
    REQUIRE(inserted->Get(1) == 99);
    delete inserted;
}
