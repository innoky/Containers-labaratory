#include "catch_amalgamated.hpp"
#include "LinkedList.hpp"

TEST_CASE("LinkedList basic append and get")
{
    LinkedList<int> list;
    list.Append(5);
    list.Append(10);
    list.Append(15);

    REQUIRE(list.Get(0) == 5);
    REQUIRE(list.Get(1) == 10);
    REQUIRE(list.Get(2) == 15);
}

TEST_CASE("LinkedList Prepend and InsertAt")
{
    LinkedList<int> list;
    list.Append(10);
    list.Prepend(5);
    list.InsertAt(1, 7);

    REQUIRE(list.Get(0) == 5);
    REQUIRE(list.Get(1) == 7);
    REQUIRE(list.Get(2) == 10);
}
