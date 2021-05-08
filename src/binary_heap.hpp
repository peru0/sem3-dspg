#pragma once

#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>

template<class T>
class BinaryHeap {
private:
    std::vector<T> m_data;

    bool is_index_in_bound(size_t index) {
        return index < m_data.size();
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

    // void insert(T&& value);
    void insert(const T& value) {
        size_t index = m_data.size();
        m_data.push_back(value);

        while (index != 0) {
            size_t parent_index = index / 2;

            // 부모보다 크면 더 이상 올라가지 않고 종료 (min-heap)
            if (m_data[index] > m_data[parent_index])
                break;

            std::swap(m_data[index], m_data[parent_index]);
            index = parent_index;
        }
    }

    T pop() {
        if (m_data.empty())
            throw std::runtime_error("attempted to pop an element from the empty heap");

        size_t last_index = m_data.size() - 1;

        // extract the top element from the heap
        T value = m_data[0];
        std::swap(m_data[0], m_data[last_index]);
        m_data.pop_back();

        down_heapify(0);

        return value;
    }

    const T& peek() const { return m_data[0]; }
};

