#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <algorithm>
#include "nlohmann/json.hpp"

//template<class T>
//class BinaryHeap {
//private:
//    std::vector<T> m_data;
//
//public:
//    explicit BinaryHeap();
//
//    void insert(T&& value);
//    const T& peek() const;
//    void pop();
//};

class Edge {
private:
    std::string m_source;
    std::string m_destination;
    float m_distance;

public:
    explicit Edge(const nlohmann::json& edge);
};

class Station {
private:
    std::string m_name;
    std::vector<std::shared_ptr<Station>> m_adjacents;

public:
    explicit Station(nlohmann::json& json);

    std::string_view name() const;
};


class Map {
private:
    std::unordered_map<std::string, std::shared_ptr<Station>> m_stations;

public:
    explicit Map(const std::string& json_path);

    void print_path(const std::string& source, const std::string& destination) const;
};
