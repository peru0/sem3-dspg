#pragma once

#include <tuple>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>

template<typename Priority, typename Value>
class BinaryHeap {
private:
    std::vector<std::pair<Priority, Value>> m_data;

    bool is_index_in_bound(size_t index) {
        return index < m_data.size();
    }

    Priority& get_priority(size_t index) {
        return m_data[index].first;
    }

    void down_heapify(size_t index) {
        while (true) {
            size_t left_index = (index * 2) + 1;
            size_t right_index = (index * 2) + 2;
            size_t min_index = index;

            if (is_index_in_bound(left_index) && m_data[min_index] > m_data[left_index])
                min_index = left_index;

            if (is_index_in_bound(right_index) && m_data[min_index] > m_data[right_index])
                min_index = right_index;

            if (min_index == index)
                break;

            std::swap(m_data[index], m_data[min_index]);
            index = min_index;
        }
    }

    void up_heapify(size_t index) {
        while (index != 0) {
            size_t parent_index = index / 2;

            if (m_data[index] > m_data[parent_index])
                break;

            std::swap(m_data[index], m_data[parent_index]);

            index = parent_index;
        }
    }

public:
    explicit BinaryHeap() : m_data() {}

    size_t size() const { return m_data.size(); }

    bool empty() const { return m_data.size() == 0; }

    void insert(const Priority& priority, const Value& value) {
        size_t index = m_data.size();
        m_data.push_back(std::make_pair(priority, value));

        while (index != 0) {
            size_t parent_index = index / 2;

            if (get_priority(index) > get_priority(parent_index))
                break;

            std::swap(m_data[index], m_data[parent_index]);
            index = parent_index;
        }
    }

    Value pop() {
        if (m_data.empty())
            throw std::runtime_error("attempted to pop an element from the empty heap");

        size_t last_index = m_data.size() - 1;

        auto value = m_data[0];
        std::swap(m_data[0], m_data[last_index]);
        m_data.pop_back();

        down_heapify(0);

        return value.second;
    }

    Value& peek() { return m_data[0]; }
};

