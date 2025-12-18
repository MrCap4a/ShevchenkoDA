#pragma once

#include "heap.h"
#include <utility>

template<typename T, typename Priority = int>
class PriorityQueue {
private:
    struct Item {
        T value;
        Priority priority;

        bool operator<(const Item& other) const {
            return priority < other.priority;
        }

        bool operator>(const Item& other) const {
            return priority > other.priority;
        }
    };

    Heap<Item> heap;

public:
    explicit PriorityQueue(bool min_priority = true) : heap(min_priority) {}

    // Добавление элемента с приоритетом - O(log n)
    void enqueue(const T& value, Priority priority);

    // Извлечение элемента с наивысшим приоритетом - O(log n)
    T dequeue();

    // Просмотр элемента с наивысшим приоритетом - O(1)
    T peek() const;

    // Проверка на пустоту - O(1)
    bool isEmpty() const { return heap.isEmpty(); }

    // Размер очереди - O(1)
    size_t size() const { return heap.size(); }
};

#include "priority_queue_impl.h"

