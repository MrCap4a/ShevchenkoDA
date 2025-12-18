#include "../include/heap.h"
#include "../include/heapsort.h"
#include "../include/priority_queue.h"
#include <iostream>
#include <vector>

void printVector(const std::vector<int> &vec) {
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i < vec.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

int main() {
  std::cout << "\n1. Min-Heap:" << std::endl;
  Heap<int> minHeap(true);
  std::vector<int> elements = {9, 5, 7, 3, 1, 8, 6, 2, 4};

  std::cout << "   Вставка элементов: ";
  printVector(elements);

  for (int elem : elements) {
    minHeap.insert(elem);
  }

  std::cout << "   Корень кучи (минимум): " << minHeap.peek() << std::endl;
  std::cout << "   Размер кучи: " << minHeap.size() << std::endl;
  std::cout << "   Визуализация кучи:" << std::endl;
  minHeap.visualize();

  std::cout << "   Извлечение элементов по возрастанию: ";
  std::vector<int> extracted;
  while (!minHeap.isEmpty()) {
    extracted.push_back(minHeap.extract());
  }
  printVector(extracted);

  std::cout << "\n2. Max-Heap:" << std::endl;
  Heap<int> maxHeap(false);

  for (int elem : elements) {
    maxHeap.insert(elem);
  }

  std::cout << "   Корень кучи (максимум): " << maxHeap.peek() << std::endl;

  std::cout << "   Извлечение элементов по убыванию: ";
  extracted.clear();
  while (!maxHeap.isEmpty()) {
    extracted.push_back(maxHeap.extract());
  }
  printVector(extracted);

  std::cout << "\n3. Построение кучи из массива (buildHeap):" << std::endl;
  std::vector<int> arr = {9, 5, 7, 3, 1, 8, 6, 2, 4};
  Heap<int> heapFromArray(true);
  heapFromArray.buildHeap(arr);

  std::cout << "   Исходный массив: ";
  printVector(arr);
  std::cout << "   Корень кучи: " << heapFromArray.peek() << std::endl;
  std::cout << "   Куча корректна: "
            << (heapFromArray.isValidHeap() ? "Да" : "Нет") << std::endl;
  std::cout << "   Визуализация кучи:" << std::endl;
  heapFromArray.visualize();

  std::cout << "\n4. Сортировка кучей (Heapsort):" << std::endl;
  std::vector<int> toSort = {9, 5, 7, 3, 1, 8, 6, 2, 4};

  std::cout << "   До сортировки: ";
  printVector(toSort);

  heapsort(toSort);

  std::cout << "   После сортировки: ";
  printVector(toSort);

  std::cout << "\n5. Приоритетная очередь:" << std::endl;
  PriorityQueue<std::string, int> pq(true);

  pq.enqueue("Низкий приоритет", 3);
  pq.enqueue("Высокий приоритет", 1);
  pq.enqueue("Средний приоритет", 2);
  pq.enqueue("Очень высокий", 0);

  std::cout << "   Размер очереди: " << pq.size() << std::endl;
  std::cout << "   Элементы в порядке приоритета:" << std::endl;

  while (!pq.isEmpty()) {
    std::cout << "     - " << pq.dequeue() << std::endl;
  }

  return 0;
}
