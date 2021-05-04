#include <vector>
#include <exception>

class UnionFind {
    std::vector<int32_t> m_parent;

public:
    explicit UnionFind(int32_t elements);

    void make_union(int32_t x_index, int32_t y_index);
    int32_t find_root(int32_t index);
    bool is_in_same_set(int32_t x_index, int32_t y_index);
};

class Graph {
    std::vector<int32_t> m_edges;
public:


};

UnionFind::UnionFind(int32_t elements) : m_parent() {
    m_parent.reserve(elements);
    for (auto i = 0; i < elements; ++i) {
        m_parent.push_back(i);
    }
}

void UnionFind::make_union(int32_t x_index, int32_t y_index) {
    // 긴 트리가 있다면 긴 트리의 자식으로 작은 쪽의 트리를 달아두는 방식으로
    // 구현하는 것이 높이를 줄일 수 있다고 소개되어 있지만, size에 대한 정보도 관리해야 하니 일단은 구분하지 않고 연결하자.
    //
    // Notes:
    // x \in A를 테스트 하는 방법으로 bloom filter도 있구나...
    // 일단 가장 어려운 건 이런 걸 사용했을 때 효과를 볼 데이터 세트를 얻는 게 가장 힘들지 않을까.
    // 일단 충분히 큰 데이터를 상대로 연산해야 "아 이거 정말로 좋구나"라고 느낄 수 있을텐데.
    auto x_root = find_root(x_index);

    m_parent[y_index] = x_root;
}

int32_t UnionFind::find_root(int32_t index) {


    int32_t id = index;
    while (id != m_parent[id]) {
        m_parent[id] = m_parent[m_parent[id]]; // path compression
        id = m_parent[id];
    }

    return id;
}

bool UnionFind::is_in_same_set(int32_t x_index, int32_t y_index) {
    auto x_root = find_root(x_index);
    auto y_root = find_root(y_index);

    return x_root == y_root;
}

int main() { return 0; }
