#pragma once

#include <vector>
#include <algorithm>

// In-place сортировка кучей (Heapsort) - O(n log n)
template<typename T>
void heapsort(std::vector<T>& arr);

// Вспомогательная функция для sift-down в in-place версии
template<typename T>
void heapifyDown(std::vector<T>& arr, size_t heap_size, size_t index, bool ascending = true);

#include "heapsort_impl.h"

