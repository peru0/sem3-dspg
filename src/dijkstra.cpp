#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "dijkstra.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::trace);

    Map map("metro.json");
    // map.print_path("서울역", "청량리(서울시립대입구)");
}

Map::Map(const std::string& json_path) : m_stations() {
    spdlog::debug("loading a data file from {}", json_path);

    if (!fs::exists(json_path))
        throw std::runtime_error(fmt::format("could not read a file: {}", json_path));

    // read json from the file
    std::ifstream file(json_path);
    nlohmann::json json;
    file >> json;

    for (std::string name : json["stations"]) {
        spdlog::trace("read a station name: {}", name);

        // 일단 데이터는 중복이 없도록 구성했고 그걸 손대지 않았다고 가정하고
        auto vertex = std::make_shared<Station>(name);
        m_stations.insert({name, vertex});
    }

    // TODO: read edges

}

Station::Station(const std::string& name) : m_name(name) {
    spdlog::trace("created a vertex: {}", name);
}
