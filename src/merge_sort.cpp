#include <spdlog/spdlog.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>

void merge_sort_impl(std::vector<int>& arr, size_t begin, size_t end, std::vector<int>& temp) {
    auto arr_len = end - begin;

    if (arr_len <= 1)
        return;

    auto mid = begin + (arr_len / 2);
    merge_sort_impl(arr, begin, mid, temp);
    merge_sort_impl(arr, mid, end, temp);

    // merge(left, right)
    // iterator를 받고 증가시키면 밑에서 복사할 때 더 짧게 쓸 수 있곘다는 생각은 들지만...
    auto offset = begin;
    auto left = begin;
    auto right = mid;

    while (left < mid && right < end) {
        if (arr[left] < arr[right]) {
            temp[offset] = arr[left];
            left += 1;
        } else {
            temp[offset] = arr[right];
            right += 1;
        }

        offset += 1;
    }

    if (left == mid)
        std::copy(arr.begin() + right, arr.begin() + end, temp.begin() + offset);
    else
        std::copy(arr.begin() + left, arr.begin() + mid, temp.begin() + offset);

    std::copy(temp.begin() + begin, temp.begin() + end, arr.begin() + begin);
}

void merge_sort(std::vector<int>& arr) {
    std::vector<int> temp(arr.size(), 0);
    merge_sort_impl(arr, 0, arr.size(), temp);
}

void check_sorted(const std::vector<int>& arr) {
    spdlog::info("checking {} elements", arr.size());

    int m = std::numeric_limits<int>::min();

    for (auto val : arr) {
        if (m > val) {
            spdlog::error("\u274C found an incorrectly sorted element: m={}, val={}", m, val);
            return;
        }

        m = val;
    }

    spdlog::info("\u2705 passed");
}

int main() {
    // int 말고도 generic한 타입 아무거나 괜찮지만...
    // 역시 template<typename T> 계속 넣기도 번거롭고
    // 제일 중요한 건 오류가 발생하면 다른 언어의 generic 기능에 비해 오류 메시지를 읽기가 상당히 골룸하단 말이지...

    std::vector<int> data;

    data = { 0, 4, 3, 7, 6, 2 };
    merge_sort(data);
    check_sorted(data);

    // ... 500만개를 랜덤으로 채우고 정렬
    data = std::vector(5e6, 0);
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> uniform(-1e6);
    for (auto i = 0; i < 1e6; i++) {
        data[i] = uniform(rng);
    }

    //    [2021-05-14 15:33:44.028] [info] sorting 5000000 elements..
    //    [2021-05-14 15:33:44.717] [info] done!
    //    [2021-05-14 15:33:44.718] [info] checking 5000000 elements
    //    [2021-05-14 15:33:44.722] [info] ✅ passed
    // 1초도 안 걸린다!
    spdlog::info("sorting {} elements..", data.size());
    merge_sort(data);
    spdlog::info("done!");
    check_sorted(data);

    return 0;
}
