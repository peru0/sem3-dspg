#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

using namespace std;

constexpr string_view METRO_JSON_PATH = "metro.json";

void binary_search(const vector<string>& stations, const string& term) {
    size_t begin = 0, mid, end = stations.size();

    cout << " ======= binary search: " << term << " =======" << endl;

    while (end - begin > 1) {
        mid = begin + ((end - begin) / 2);

        cout << "data[" << begin << "..(" << mid << ").." << end << "]" << endl;

        if (stations[mid] == term) {
            cout << "data[" << mid << "] 에 존재" << endl;
            return;
        } else if (term < stations[mid]) {
            end = mid;
        } else if (term > stations[mid]) {
            begin = mid;
        }
    }

    cout << "결과 없음" << endl;
}


int main() {
    if (!filesystem::exists(METRO_JSON_PATH)) {
        cout << "file " << METRO_JSON_PATH << " does not exist!" << endl;
        return 1;
    }

    ifstream metro_file;
    metro_file.open(METRO_JSON_PATH, ios::in);

    if (!metro_file.is_open()) {
        cout << "could not open a file " << METRO_JSON_PATH << endl;
        return 1;
    }

    nlohmann::json metro_json;
    metro_file >> metro_json;

    vector<string> data;
    for (const string& name : metro_json["stations"]) {
        data.push_back(name);
    }

    sort(data.begin(), data.end());

    binary_search(data, "가락시장");
    binary_search(data, "가산디지털단지");
    binary_search(data, "서울역");
    binary_search(data, "홍대입구");
    binary_search(data, "수퍼빌런");

}
