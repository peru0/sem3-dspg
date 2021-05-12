#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "binary_heap.hpp"

TEST_CASE("Test binary heap", "[binary heap]" ) {
    BinaryHeap<int, int> heap;

    SECTION("inserting elements in descending order") {
        heap.insert(5, 42);
        heap.insert(4, 43);
        heap.insert(3, 44);
        heap.insert(2, 45);
        heap.insert(1, 46);

        REQUIRE(heap.pop() == 46);
        REQUIRE(heap.pop() == 45);
        REQUIRE(heap.pop() == 44);
        REQUIRE(heap.pop() == 43);
        REQUIRE(heap.pop() == 42);
    }
}
