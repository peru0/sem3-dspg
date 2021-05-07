#include <cstddef>
#include <vector>
#include <exception>
#include <stdexcept>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
//#include <format>

class UnionFind {
    std::vector<size_t> m_parents;
    std::vector<size_t> m_weights;
public:
    // C++에 아직 안 익숙해서 아직 언제 copy-init가 일어나는 지 잘 모르니까...
    explicit UnionFind(size_t elements) : m_parents(), m_weights(elements, 1) {
        m_parents.reserve(elements);
        for (int i = 0; i < elements; i++) {
            m_parents.push_back(i);
        }
    }

    void make_union(size_t x_index, size_t y_index) {
        auto x_root = find_root(x_index);
        auto y_root = find_root(y_index);

        auto x_weight = m_weights[x_root];
        auto y_weight = m_weights[y_root];

        if (x_weight < y_weight) {
            // Let x be the child of y
            m_parents[x_root] = y_root;
            m_weights[y_root] += m_weights[x_root];
        } else {
            // Let y be the child of x
            m_parents[y_root] = x_root;
            m_weights[x_root] += m_weights[y_root];
        }
    }

    size_t find_root(size_t index) {
        size_t id = index;
        while (id != m_parents[id]) {
            m_parents[id] = m_parents[m_parents[id]];
            id = m_parents[id];
        }

        return id;
    }

    bool is_in_same_set(size_t x_index, size_t y_index) {
        auto x_root = find_root(x_index);
        auto y_root = find_root(y_index);

        return x_root == y_root;
    }
};

struct Edge {
    size_t source;
    size_t destination;
    uint32_t weight;
};

class Graph {
    // kruskal 구현할 때 가장 까다롭다고 느낀 게
    // 일단 그래프 내의 모든 edge 목록을 따로 가지고 있어야 오름차순으로 정렬할 때 logN이나 NlogN 안에 가능한데
    // (아니면 모든 정점을 순회하고 나서야 edges를 정렬할 수 있으니까...)
    //
    // 이러면 vertex를 그래프에서 삭제하는 연산이 필요할 때
    // (예를 들어 게임 내에서 문이 열리고 닫힐 때마다 NPC가 지나가지 못하는 경로를 찾지 못 하도록 실내/실외를 연결하는 간선이 변한다던가)
    // edges를 전부 조회하고 배열에서 삭제하는 연산을 해야 한단 말이지...
    //
    // 아무래도 다익스트라를 구현할 때 고려해봐야겠다.
    std::vector<std::string> m_vertices;
    std::vector<Edge> m_edges;

public:
    explicit Graph() : m_vertices(), m_edges() {
    }

    void insert_node(const std::string& name) {
        // 'take ownership of name'을 쉽게 할 방법이 없고 그냥 복사...
        m_vertices.push_back(name);
    }

    template<class StringIteratorType>
    void insert_node(StringIteratorType begin, StringIteratorType end) {
        for (; begin != end; begin++) {
            insert_node(*begin);
        }
    }

    void insert_edge(const Edge& edge) {
        if (edge.source < 0 || edge.source > m_edges.size())
            // https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance?view=msvc-160
            // P0645R10 <format> Text Formatting 	No
//            throw std::exception(std::format("index '{}' is invalid"));
            throw std::runtime_error("provided source vertex index is invalid");

        if (edge.source < 0 || edge.source > m_edges.size())
            throw std::runtime_error("provided destination vertex index is invalid");

        m_edges.push_back(edge);
    }

    template<class IteratorType>
    void insert_edge(IteratorType begin, IteratorType end) {
        for (; begin != end; begin++) {
            insert_edge(*begin);
        }
    }

    void print_kruskal_mst() {
        UnionFind sets{m_vertices.size()};

//        std::vector<Edge> path{};
//        path.reserve(m_vertices.size());

        std::sort(m_edges.begin(), m_edges.end(), [] (const Edge& lhs, const Edge& rhs) {
            return lhs.weight < rhs.weight;
        });

        size_t total_weight = 0;
        size_t num_connected = 0;

        for (const Edge& edge : m_edges) {
            if (sets.is_in_same_set(edge.source, edge.destination)) {
                std::cout
                        << "connecting "
                        << m_vertices[edge.source]
                        << " <-" << edge.weight  << "-> "
                        << m_vertices[edge.destination]
                        << " would make a cycle, skipping.."
                        << std::endl;
                continue;
            }

//            path.push_back(edge.source);

            std::cout
                << m_vertices[edge.source]
                << " <-" << edge.weight  << "-> "
                << m_vertices[edge.destination]
                << std::endl;
            sets.make_union(edge.source, edge.destination);

            total_weight += edge.weight;
            num_connected += 1;

            if (num_connected + 1 >= m_vertices.size()) {
                std::cout << "|S| + 1 == |V|" << std::endl;
                break;
            }
        }

        std::cout << "connected edges: " << num_connected << std::endl;
        std::cout << "total weight: " << total_weight << std::endl;
    }
};

int main() {
    Graph graph{};

    //
    //   1 - 2 - 3
    //  /     \   \
    // 0 ----- 4 -- 5 - 6 - 7
    //  \          /
    //   +--------+
    //
    std::vector<std::string> vertices {
        "0", "1", "2", "3", "4", "5", "6", "7"
    };
    std::vector<Edge> edges {
        { .source=0, .destination=1, .weight=1 },
        { .source=0, .destination=4, .weight=2 },
        { .source=0, .destination=5, .weight=10 },
        { .source=1, .destination=2, .weight=2 },
        { .source=2, .destination=3, .weight=4 },
        { .source=2, .destination=4, .weight=2 },
        { .source=3, .destination=5, .weight=3 },
        { .source=4, .destination=5, .weight=6 },
        { .source=5, .destination=6, .weight=3 },
        { .source=6, .destination=7, .weight=4 },
    };

    graph.insert_node(vertices.begin(), vertices.end());
    graph.insert_edge(edges.begin(), edges.end());

    //   1 - 2
    //  /     \
    // 0 ----- 4
    //    ^^^^
    // 예를 들어 이건 사이클을 만들기 때문에 스킵해야 함 (stable_sort가 아니라 이게 먼저 연결되면 문제 없긴 하지만...)
    graph.print_kruskal_mst();

    // 최소비용으로 신장한 모습
    //   1 - 2 - 3
    //  /         \
    // 0 ----- 4    5 - 6 - 7

    return 0;
}
