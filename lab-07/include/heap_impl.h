template<typename T>
void Heap<T>::siftUp(size_t index) {
    while (index > 0 && compare(data[index], data[parent(index)])) {
        std::swap(data[index], data[parent(index)]);
        index = parent(index);
    }
}

template<typename T>
void Heap<T>::siftDown(size_t index) {
    while (true) {
        size_t target = index;
        size_t l = left(index);
        size_t r = right(index);

        if (l < data.size() && compare(data[l], data[target])) {
            target = l;
        }
        if (r < data.size() && compare(data[r], data[target])) {
            target = r;
        }

        if (target == index) {
            break;
        }

        std::swap(data[index], data[target]);
        index = target;
    }
}

template<typename T>
void Heap<T>::insert(const T& value) {
    data.push_back(value);
    siftUp(data.size() - 1);
}

template<typename T>
T Heap<T>::extract() {
    if (data.empty()) {
        throw std::runtime_error("Heap is empty");
    }

    T root = data[0];
    data[0] = data.back();
    data.pop_back();

    if (!data.empty()) {
        siftDown(0);
    }

    return root;
}

template<typename T>
T Heap<T>::peek() const {
    if (data.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return data[0];
}

template<typename T>
void Heap<T>::buildHeap(const std::vector<T>& arr) {
    data = arr;
    
    // Начинаем с последнего нелистового узла
    for (int i = static_cast<int>(data.size() / 2) - 1; i >= 0; --i) {
        siftDown(static_cast<size_t>(i));
    }
}

template<typename T>
bool Heap<T>::isValidHeap() const {
    for (size_t i = 0; i < data.size(); ++i) {
        size_t l = left(i);
        size_t r = right(i);

        if (l < data.size() && !compare(data[i], data[l])) {
            return false;
        }
        if (r < data.size() && !compare(data[i], data[r])) {
            return false;
        }
    }
    return true;
}

template<typename T>
void Heap<T>::visualizeNode(size_t index, int depth, const std::string& prefix, bool isLast) const {
    if (index >= data.size()) {
        return;
    }

    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << data[index] << std::endl;

    size_t l = left(index);
    size_t r = right(index);
    bool hasLeft = l < data.size();
    bool hasRight = r < data.size();

    if (hasLeft || hasRight) {
        std::string newPrefix = prefix + (isLast ? "    " : "│   ");
        if (hasLeft && hasRight) {
            visualizeNode(l, depth + 1, newPrefix, false);
            visualizeNode(r, depth + 1, newPrefix, true);
        } else if (hasLeft) {
            visualizeNode(l, depth + 1, newPrefix, true);
        } else if (hasRight) {
            visualizeNode(r, depth + 1, newPrefix, true);
        }
    }
}

template<typename T>
void Heap<T>::visualize() const {
    if (data.empty()) {
        std::cout << "(пустая куча)" << std::endl;
        return;
    }

    std::cout << (is_min_heap ? "Min-Heap:" : "Max-Heap:") << std::endl;
    visualizeNode(0, 0, "", true);
}

