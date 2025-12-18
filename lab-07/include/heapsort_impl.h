template<typename T>
void heapifyDown(std::vector<T>& arr, size_t heap_size, size_t index, bool ascending) {
    while (true) {
        size_t target = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (ascending) {
            if (left < heap_size && arr[left] > arr[target]) {
                target = left;
            }
            if (right < heap_size && arr[right] > arr[target]) {
                target = right;
            }
        } else {
            if (left < heap_size && arr[left] < arr[target]) {
                target = left;
            }
            if (right < heap_size && arr[right] < arr[target]) {
                target = right;
            }
        }

        if (target == index) {
            break;
        }

        std::swap(arr[index], arr[target]);
        index = target;
    }
}

template<typename T>
void heapsort(std::vector<T>& arr) {
    if (arr.empty()) {
        return;
    }

    // Построение max-heap - O(n)
    for (int i = static_cast<int>(arr.size() / 2) - 1; i >= 0; --i) {
        heapifyDown(arr, arr.size(), static_cast<size_t>(i), true);
    }

    // Извлечение элементов из кучи - O(n log n)
    for (size_t i = arr.size() - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapifyDown(arr, i, 0, true);
    }
}

