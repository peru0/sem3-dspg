#include "binary_heap.hpp"
#include <spdlog/spdlog.h>
#include <vector>
#include <limits>

int main() {
    // 이미 binary_heap.hpp에서 구현했던 것
    BinaryHeap<int, int> heap;

    spdlog::info("inserting 5m elements to the heap...");
    for (auto i = 0; i < 5 * 1e6; i++) {
        auto p = i % 1000;
        heap.insert(p, p);
    }
//    Release
//    [2021-05-14 16:56:12.584] [info] inserting 5m elements to the heap...
//    [2021-05-14 16:56:12.689] [info] <...>
//    [2021-05-14 16:56:14.324] [info] ✅ passed!
    spdlog::info("<...>");
    auto m = std::numeric_limits<int>::min();
    while (!heap.empty()) {
        auto val = heap.pop();
        if (val < m) {
            spdlog::error("❌ something is wrong: m={}, val={}", m, val);
            return -1;
        }
    }

    spdlog::info("✅ passed!");
    return 0;
}
