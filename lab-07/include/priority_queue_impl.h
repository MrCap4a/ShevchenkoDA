template<typename T, typename Priority>
void PriorityQueue<T, Priority>::enqueue(const T& value, Priority priority) {
    heap.insert(Item{value, priority});
}

template<typename T, typename Priority>
T PriorityQueue<T, Priority>::dequeue() {
    Item item = heap.extract();
    return item.value;
}

template<typename T, typename Priority>
T PriorityQueue<T, Priority>::peek() const {
    Item item = heap.peek();
    return item.value;
}

