#include <string>
#include <fstream>
#include <filesystem>
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "dijkstra.h"

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::trace);

    Map map("stations.json");
    map.print_path("서울역", "청량리(서울시립대입구)");
}

//template<class T>
//BinaryHeap<T>::BinaryHeap() : m_data() { }
//
//template<class T>
//void BinaryHeap<T>::insert(T &&value) {
//    size_t index = m_data.size();
//    m_data.push_back(value);
//
//    // 루트가 아니면 계속 부모와 비교해서 교환
//    while (index != 0) {
//        size_t parent_index = index / 2;
//        if (m_data[index] < m_data[parent_index]) {
//            std::swap(m_data[index], m_data[parent_index]);
//        }
//
//        index = parent_index;
//    }
//}
//
//template<class T>
//const T& BinaryHeap<T>::peek() const {
//    return m_data[0];
//}
//
//template<class T>
//void BinaryHeap<T>::pop() {
//    size_t last_index = m_data.size() - 1;
//
//    // delete the first element from the heap
//    std::swap(m_data[0], m_data[last_index]);
//    m_data.pop_back();
//
//    size_t index = 0;
//    while (true) {
//        auto left_index = (index * 2) + 1;
//        auto right_index = (index * 2) + 2;
//        auto min_index = index;
//
//        if (left_index < m_data.len() && m_data[min_index] > m_data[left_index])
//            min_index = left_index;
//
//        if (right_index < m_data.len() && m_data[min_index] > m_data[right_index])
//            min_index = right_index;
//
//        if (index == min_index)
//            break;
//
//        std::swap(m_data[index], m_data[min_index]);
//
//        index = min_index;
//    }
//}
//


Map::Map(const std::string& json_path) : m_stations() {
    if (!fs::exists(json_path))
        throw std::runtime_error(fmt::format("unable to read a file: {}", json_path));

    // read json from the file
    std::ifstream stations_file(json_path);
    nlohmann::json stations_json;
    stations_file >> stations_json;

    for (const nlohmann::json& vertex_json : stations_json) {
        std::string name = vertex_json["name"];


        vertex["adjacents"];

    }
}
