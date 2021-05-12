#pragma once

#include "binary_heap.hpp"
#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <algorithm>

struct Edge {
    uint32_t source_id;
    uint32_t dest_id;
    float distance;
};

struct Station {
    uint32_t id;
    std::string name;
    std::vector<struct Edge> edges;
};

class Map {
private:
    std::vector<std::shared_ptr<Station>> m_stations;
    std::unordered_map<std::string, std::shared_ptr<Station>> m_lookup;

public:
    explicit Map(const std::string& json_path);
    void print_path(const std::string& source_name, const std::string& dest_name);
};
