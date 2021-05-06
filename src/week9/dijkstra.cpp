#include <string>
#include <fstream>
#include <filesystem>
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "dijkstra.h"

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::trace);

    Map map("stations.json");
    map.print_path("서울역", "청량리(서울시립대입구)");
}

Map::Map(const std::string& json_path) : m_stations() {
    if (!fs::exists(json_path))
        throw std::runtime_error(fmt::format("unable to read a file: {}", json_path));

    // read json from the file
    std::ifstream file(json_path);
    nlohmann::json json;
    file >> json;

    // load vertices from the file
    for (std::string name : json["stations"]) {
        spdlog::trace(">> {}", name);
    }
}
