#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

template<typename T>
class Heap {
private:
    std::vector<T> data;
    bool is_min_heap;

    // Индекс родителя
    size_t parent(size_t i) const { return (i - 1) / 2; }
    
    // Индекс левого потомка
    size_t left(size_t i) const { return 2 * i + 1; }
    
    // Индекс правого потомка
    size_t right(size_t i) const { return 2 * i + 2; }

    // Проверка свойства кучи для min-heap или max-heap
    bool compare(const T& a, const T& b) const {
        return is_min_heap ? (a < b) : (a > b);
    }

    // Всплытие элемента вверх (sift-up) - O(log n)
    void siftUp(size_t index);

    // Погружение элемента вниз (sift-down) - O(log n)
    void siftDown(size_t index);

public:
    explicit Heap(bool min_heap = true) : is_min_heap(min_heap) {}
    
    Heap(const std::vector<T>& arr, bool min_heap = true) : is_min_heap(min_heap) {
        buildHeap(arr);
    }

    // Вставка элемента - O(log n)
    void insert(const T& value);

    // Извлечение корня - O(log n)
    T extract();

    // Просмотр корня без извлечения - O(1)
    T peek() const;

    // Построение кучи из массива - O(n)
    void buildHeap(const std::vector<T>& arr);

    // Проверка на пустоту - O(1)
    bool isEmpty() const { return data.empty(); }

    // Размер кучи - O(1)
    size_t size() const { return data.size(); }

    // Получение всех элементов (для тестирования)
    std::vector<T> getData() const { return data; }

    // Проверка свойства кучи (для тестирования)
    bool isValidHeap() const;

    // Визуализация кучи в виде дерева
    void visualize() const;
    
private:
    // Вспомогательная функция для визуализации
    void visualizeNode(size_t index, int depth, const std::string& prefix, bool isLast) const;
};

#include "heap_impl.h"

