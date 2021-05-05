#pragma once

#include <memory>
#include <string>
#include <string_view>

class Station {
private:
    std::string m_name;
    std::vector<std::shared_ptr<Station>> m_adjacents;

public:
    explicit Station(const std::string& name);

    std::string_view name() const;
};


class Map {
private:

public:
    Map(const std::string& vertices_path, const std::string& edges_path);
};
