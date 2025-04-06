#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../include/ImmutableArraySequence.hpp"

TEST_CASE("ImmutableArraySequence basic functionality", "[ImmutableArraySequence]")
{
    int rawData[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> seq(rawData, 5);

    SECTION("Get elements")
    {
        REQUIRE(seq.GetFirst() == 1);   
        REQUIRE(seq.GetLast() == 5);
        REQUIRE(seq.Get(2) == 3);
    }

    SECTION("Length")
    {
        REQUIRE(seq.GetLength() == 5);
    }

    SECTION("SubSequence")
    {
        auto sub = seq.GetSubSequence(1, 4);
        REQUIRE(sub->GetLength() == 3);
        REQUIRE(sub->Get(0) == 2);
        REQUIRE(sub->Get(2) == 4);
        delete sub;
    }

    SECTION("Concat")
    {
        ImmutableArraySequence<int> other(rawData, 2);
        auto concat = seq.Concat(other);
        REQUIRE(concat->GetLength() == 7);
        REQUIRE(concat->Get(0) == 1);
        REQUIRE(concat->Get(6) == 2);
        delete concat;
    }
}
