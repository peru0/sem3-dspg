#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "dijkstra.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::debug);

    Map map("metro.json");
    map.print_path("서울역", "청량리(서울시립대입구)");
}

Map::Map(const std::string& json_path) : m_stations() {
    spdlog::debug("loading a data file from {}", json_path);

    if (!fs::exists(json_path))
        throw std::runtime_error(fmt::format("could not read a file: {}", json_path));

    // read json from the file
    std::ifstream file(json_path);
    nlohmann::json json;
    file >> json;

    for (const nlohmann::json& station_json : json["stations"]) {
        const std::string& name = station_json;
        spdlog::trace("read a station name: {}", name);

        // 일단 데이터는 중복이 없도록 구성했고 그걸 손대지 않았다고 가정하고
        auto vertex = std::make_shared<Station>(name);
        m_stations.insert({name, vertex});
    }

    for (const nlohmann::json& edge_json : json["edges"]) {
        const std::string& source = edge_json["source"];
        const std::string& destination = edge_json["destination"];
        float distance = edge_json["distance"];

        // 편도나 급행이 없다고 가정.
        // ...사실 방향 그래프로 표현하고 있으니 맞는 데이터만 준비해서 edge를 연결하면 된다고 생각하지만...
        m_stations[source]->insert_edge(m_stations[destination], distance);
        m_stations[destination]->insert_edge(m_stations[source], distance);
    }
}

void Map::print_path(const std::string& source, const std::string& destination) const {
    spdlog::debug("find a path from {} to {}", source, destination);

    std::shared_ptr<Station> src_node = m_stations.at(source);
    std::shared_ptr<Station> dest_node = m_stations.at(destination);

    // TODO

}

Station::Station(const std::string& name) : m_name(name) {
    spdlog::trace("created a vertex: {}", name);
}

void Station::insert_edge(std::shared_ptr<Station> destination, float distance) {
    spdlog::trace("inserting a edge: {} <-({}km)-> {}", m_name, distance, destination->m_name);

    Edge edge {
        .destination = destination,
        .distance = distance,
    };

    m_adjacents.insert(edge);
}

bool Edge::operator>(const Edge &rhs) const {
    return this->distance > rhs.distance;
}
