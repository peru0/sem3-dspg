#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool search_sorted(const vector<string>& data, const string& value) {
    auto count = 1;
    for (const auto& v : data) {
        if (value < v) {
            // 이미 나올 수 있는 공간을 넘어감
            cout << count << "회 검색 후 => 원소를 찾지 못함 ('" << value << "' < '" << v << "')" << endl;
            return false;
        } else if (value == v) {
            cout << count << "회 검색 후 원소를 찾음" << endl;
            return true;
        }

        count += 1;
    }

    cout << count << "회 읽고 => 원소를 찾지 못함" << endl;
    return false;
}

int main() {
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_cmp
    // 다행히 사전 순으로 비교가 가능
    vector<string> data {
        "AAA", "BBBBB", "CCCCC", "가위", "바나나", "다람쥐", "42", "0"
    };

    // 일단 데이터 자체는 정렬이 안 되어 있을 수도 있으니 정렬
    sort(data.begin(), data.end());

    search_sorted(data, "CCCCC");
    search_sorted(data, "Canada");
    search_sorted(data, "바나나");
    search_sorted(data, "바위");
    search_sorted(data, "키위");

    return 0;
}
