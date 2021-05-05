#include <string>
#include <fstream>
#include <filesystem>
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "prim.h"

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::trace);
    try {
        Map map("vertices.json", "edges.json");
    } catch (const std::exception& ex) {
        spdlog::error("{}", ex.what());
    }
}

Station::Station(const std::string& name) : m_name(name) {
    //
}

std::string_view Station::name() const {
    return m_name;
}

Map::Map(const std::string &vertices_path, const std::string &edges_path) {
    if (!fs::exists(vertices_path))
        throw std::runtime_error(fmt::format("unable to read a file: {}", vertices_path));

    if (!fs::exists(edges_path))
        throw std::runtime_error(fmt::format("unable to read a file: {}", edges_path));

    std::ifstream vertices_file(vertices_path);
    std::ifstream edges_file(edges_path);

    nlohmann::json vertices;
    nlohmann::json edges;

    vertices_file >> vertices;
    edges_file >> edges;

    for (const nlohmann::json& vertex : vertices) {
        std::string name = vertex["name"];
    }

    for (const nlohmann::json& edge : edges) {
        std::string source = edge["source"];
        std::string dest = edge["destination"];
        float dist = edge["distance"];
    }

}
