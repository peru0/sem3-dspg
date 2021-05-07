#pragma once

#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <algorithm>

class Station {
private:
    std::string m_name;

public:
    explicit Station(const std::string& name);
};

class Map {
private:
    std::unordered_map<std::string, std::shared_ptr<Station>> m_stations;

public:
    explicit Map(const std::string& json_path);
    // void print_path(const std::string& source, const std::string& destination) const;
};
