#include <iostream>
#include <vector>
#include <string>

using namespace std;

void search(const vector<string>& data, const string& value) {
    cout << "'" << value << "' 검색:" << endl;

    auto count = 0;
    for (const auto& v : data) {
        count += 1;
        if (v == value) {
            cout << count << "회 읽고 값을 찾음" << endl;
            return;
        }
    }

    cout << count << "회 수행 후 실패" << endl;
}


int main() {
    vector<string> data {
        "Hello", "My", "Name", "Is", "John Doe",
        "Something", "42", "AAAAA", "last"
    };

    search(data, "42");
    search(data, "last");
    search(data, "Hello");
    search(data, "nobody");

    return 0;
}
