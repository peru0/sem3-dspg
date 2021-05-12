#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "dijkstra_metro.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include <limits>

namespace fs = std::filesystem;

int main() {
    spdlog::set_level(spdlog::level::debug);

    Map map("metro.json");
    //map.print_path("서울역", "청량리(서울시립대입구)");
    map.print_path("서울역", "고속터미널");
}

Map::Map(const std::string& json_path) : m_stations() {
    spdlog::debug("loading a data file from {}", json_path);

    if (!fs::exists(json_path))
        throw std::runtime_error(fmt::format("could not read a file from {}", json_path));

    // read json from the file
    std::ifstream file(json_path);
    nlohmann::json json;
    file >> json;

    // 역 정보 불러들이기
    uint32_t seq_id = 0;
    for (const nlohmann::json& station_json : json["stations"]) {
        const std::string& name = station_json;
        auto vertex = std::make_shared<Station>(seq_id, name);

        m_stations.push_back(vertex);
        m_lookup[name] = vertex;

        seq_id += 1;
    }

    // 역 연결 정보
    for (const nlohmann::json& edge_json : json["edges"]) {
        const std::string& source_name = edge_json["source"];
        const std::string& dest_name = edge_json["destination"];
        float distance = edge_json["distance"];

        // 편도나 급행이 없다고 가정.
        // ...사실 방향 그래프로 표현하고 있으니 맞는 데이터만 준비해서 edge를 연결하면 된다고 생각하지만...
        auto source = m_lookup.at(source_name);
        auto dest = m_lookup.at(dest_name);

        m_lookup.at(source_name)->edges.push_back(Edge {
            .source_id = source->id,
            .dest_id = dest->id,
            .distance = distance,
        });
        m_lookup.at(dest_name)->edges.push_back(Edge {
            .source_id = dest->id,
            .dest_id = source->id,
            .distance = distance,
        });
    }
}

void Map::print_path(const std::string& source_name, const std::string& dest_name) {
    spdlog::debug("finding a path from {} to {}", source_name, dest_name);

    auto source_node = m_lookup.at(source_name);
    auto dest_node = m_lookup.at(dest_name);

    std::vector<bool> visited(m_stations.size());
    std::vector<float> distance(m_stations.size(), std::numeric_limits<float>::infinity());
    std::vector<std::shared_ptr<Station>> updated_by(m_stations.size(), nullptr);
    BinaryHeap<float, std::shared_ptr<Station>> queue;

    distance[source_node->id] = 0.0f;
    queue.insert(0.0f, source_node);

    while (!queue.empty()) {
        auto v = queue.pop();

        if (v == dest_node) {
            spdlog::debug("found the destination (total distance {}km)", distance[v->id]);
            break;
        }

        if (visited[v->id])
            continue;
        visited[v->id] = true;

        for (const auto& edge : v->edges) {
            auto new_dist = distance[v->id] + edge.distance;
            auto old_dist = distance[edge.dest_id];

            if (new_dist < old_dist) {
                distance[edge.dest_id] = new_dist;
                updated_by[edge.dest_id] = v;

                queue.insert(new_dist, m_stations[edge.dest_id]);
            }
        }
    }

    // 찾은 경로를 출력
    spdlog::info("{} -> {} (total {:.2f}km)", source_name, dest_name, distance[dest_node->id]);

    auto node = dest_node;
    while (node != source_node) {
        spdlog::info("↑ {} ({:.2f}km)", node->name, distance[node->id]);
        node = updated_by[node->id];
    }
    spdlog::info("{} (출발역)", node->name);
}

