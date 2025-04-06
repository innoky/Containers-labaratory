#include "catch_amalgamated.hpp"
#include "DynamicArray.hpp"

TEST_CASE("DynamicArray basic operations")
{
    DynamicArray<int> arr(3);
    arr.Set(0, 42);
    arr.Set(1, 1337);
    arr.Set(2, -1);

    REQUIRE(arr.Get(0) == 42);
    REQUIRE(arr.Get(1) == 1337);
    REQUIRE(arr.Get(2) == -1);
    REQUIRE(arr.GetSize() == 3);
}

TEST_CASE("DynamicArray resize works")
{
    DynamicArray<int> arr(2);
    arr.Set(0, 1);
    arr.Set(1, 2);
    arr.Resize(4);
    arr.Set(2, 3);
    arr.Set(3, 4);

    REQUIRE(arr.Get(3) == 4);
    REQUIRE(arr.GetSize() == 4);
}
