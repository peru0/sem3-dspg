#pragma once

#include "binary_heap.hpp"
#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <algorithm>

class Station {
private:
    std::string m_name;
    BinaryHeap<struct Edge> m_adjacents;

public:
    explicit Station(const std::string& name);

    void insert_edge(std::shared_ptr<Station> destination, float distance);
};

struct Edge {
    std::shared_ptr<Station> destination;
    float distance;

    bool operator>(const Edge& rhs) const;
};

class Map {
private:
    std::unordered_map<std::string, std::shared_ptr<Station>> m_stations;

public:
    explicit Map(const std::string& json_path);
    void print_path(const std::string& source, const std::string& destination) const;
};
