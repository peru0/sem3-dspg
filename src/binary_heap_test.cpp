#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "binary_heap.hpp"

TEST_CASE("Test binary heap", "[binary heap]" ) {
    BinaryHeap<int> heap;

    SECTION("inserting elements in descending order") {
        heap.insert(5);
        heap.insert(4);
        heap.insert(3);
        heap.insert(2);
        heap.insert(1);

        REQUIRE(heap.pop() == 1);
        REQUIRE(heap.pop() == 2);
        REQUIRE(heap.pop() == 3);
        REQUIRE(heap.pop() == 4);
        REQUIRE(heap.pop() == 5);
    }
}
