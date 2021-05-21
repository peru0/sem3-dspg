#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <filesystem>


using namespace std;

constexpr string_view METRO_JSON_PATH = "metro.json";
constexpr size_t INDEX_SIZE = 32;

vector<string> build_index(const vector<string>& data) {
    vector<string> index;

    for (auto i = 0; i < data.size(); i += INDEX_SIZE) {
        index.push_back(data[i]);
    }

    return index;
}


bool try_find_index_impl(const vector<string>& index, const string& term, size_t& out_index) {
    for (auto i = 0; i < index.size() - 1; ++i) {
        if (index[i] <= term && term < index[i + 1]) {
            out_index = i;
            return true;
        }
    }

    return false;
}


void search_indexed(const vector<string>& data, const vector<string> index, const string& term) {
    size_t found_index, begin, end;
    if (try_find_index_impl(index, term, found_index)) {
        begin = found_index * INDEX_SIZE;
        end = (found_index + 1) * INDEX_SIZE;
    } else {
        begin = (index.size() - 1) * INDEX_SIZE;
        end = data.size();
    }

    cout << "====== finding a station named " << term << " in data[" << begin << ".." << end << "] ======" << endl;

    for (auto i = begin; i < end; i++) {
        if (data[i] == term) {
            cout << "found a station '" << term << "' (data[" << i << "])" << endl;
            return;
        }
    }

    cout << "can't find a station: '" << term << "'" << endl;
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
    metro_json << metro_file;

    vector<string> data;
    for (const string& name : metro_json["stations"]) {
        data.push_back(name);
    }

    sort(data.begin(), data.end());

    auto index = build_index(data);
    search_indexed(data, index, "역이름");
    search_indexed(data, index, "후후후");
    search_indexed(data, index, "서울역");
    search_indexed(data, index, "강동");
    search_indexed(data, index, "홍대입구");

    return 0;
}
