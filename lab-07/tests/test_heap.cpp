#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "../include/heap.h"
#include "../include/heapsort.h"
#include "../include/priority_queue.h"

// Тесты для Min-Heap
class MinHeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        heap = new Heap<int>(true);
    }
    
    void TearDown() override {
        delete heap;
    }
    
    Heap<int>* heap;
};

TEST_F(MinHeapTest, InsertSingleElement) {
    heap->insert(5);
    EXPECT_FALSE(heap->isEmpty());
    EXPECT_EQ(heap->size(), 1);
    EXPECT_EQ(heap->peek(), 5);
    EXPECT_TRUE(heap->isValidHeap());
}

TEST_F(MinHeapTest, InsertMultipleElements) {
    std::vector<int> elements = {5, 3, 7, 2, 4, 6, 8, 1};
    
    for (int elem : elements) {
        heap->insert(elem);
        EXPECT_TRUE(heap->isValidHeap());
    }
    
    EXPECT_EQ(heap->size(), elements.size());
    EXPECT_EQ(heap->peek(), 1);
}

TEST_F(MinHeapTest, ExtractMin) {
    heap->insert(5);
    heap->insert(3);
    heap->insert(7);
    heap->insert(1);
    heap->insert(4);
    
    EXPECT_EQ(heap->extract(), 1);
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->extract(), 3);
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->extract(), 4);
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->extract(), 5);
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->extract(), 7);
    EXPECT_TRUE(heap->isEmpty());
}

TEST_F(MinHeapTest, ExtractFromEmptyHeap) {
    EXPECT_THROW(heap->extract(), std::runtime_error);
    EXPECT_THROW(heap->peek(), std::runtime_error);
}

TEST_F(MinHeapTest, BuildHeapFromArray) {
    std::vector<int> arr = {9, 5, 7, 3, 1, 8, 6, 2, 4};
    heap->buildHeap(arr);
    
    EXPECT_EQ(heap->size(), arr.size());
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->peek(), 1);
}

TEST_F(MinHeapTest, ExtractAllElements) {
    std::vector<int> elements = {5, 3, 7, 2, 4, 6, 8, 1};
    
    for (int elem : elements) {
        heap->insert(elem);
    }
    
    std::vector<int> extracted;
    while (!heap->isEmpty()) {
        extracted.push_back(heap->extract());
        EXPECT_TRUE(heap->isValidHeap());
    }
    
    std::sort(elements.begin(), elements.end());
    EXPECT_EQ(extracted, elements);
}

// Тесты для Max-Heap
class MaxHeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        heap = new Heap<int>(false);
    }
    
    void TearDown() override {
        delete heap;
    }
    
    Heap<int>* heap;
};

TEST_F(MaxHeapTest, InsertAndExtractMax) {
    heap->insert(5);
    heap->insert(3);
    heap->insert(7);
    heap->insert(1);
    heap->insert(4);
    
    EXPECT_EQ(heap->peek(), 7);
    EXPECT_EQ(heap->extract(), 7);
    EXPECT_EQ(heap->extract(), 5);
    EXPECT_EQ(heap->extract(), 4);
    EXPECT_EQ(heap->extract(), 3);
    EXPECT_EQ(heap->extract(), 1);
    EXPECT_TRUE(heap->isEmpty());
}

TEST_F(MaxHeapTest, BuildMaxHeapFromArray) {
    std::vector<int> arr = {9, 5, 7, 3, 1, 8, 6, 2, 4};
    heap->buildHeap(arr);
    
    EXPECT_EQ(heap->size(), arr.size());
    EXPECT_TRUE(heap->isValidHeap());
    EXPECT_EQ(heap->peek(), 9);
}

// Тесты для Heapsort
class HeapsortTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(HeapsortTest, SortEmptyArray) {
    std::vector<int> arr;
    heapsort(arr);
    EXPECT_TRUE(arr.empty());
}

TEST_F(HeapsortTest, SortSingleElement) {
    std::vector<int> arr = {5};
    heapsort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 5);
}

TEST_F(HeapsortTest, SortSortedArray) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = arr;
    heapsort(arr);
    EXPECT_EQ(arr, expected);
}

TEST_F(HeapsortTest, SortReverseSortedArray) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    heapsort(arr);
    EXPECT_EQ(arr, expected);
}

TEST_F(HeapsortTest, SortRandomArray) {
    std::vector<int> arr = {9, 5, 7, 3, 1, 8, 6, 2, 4};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    heapsort(arr);
    EXPECT_EQ(arr, expected);
}

TEST_F(HeapsortTest, SortLargeArray) {
    std::vector<int> arr(1000);
    std::iota(arr.begin(), arr.end(), 1);
    std::reverse(arr.begin(), arr.end());
    
    std::vector<int> expected(1000);
    std::iota(expected.begin(), expected.end(), 1);
    
    heapsort(arr);
    EXPECT_EQ(arr, expected);
}

TEST_F(HeapsortTest, SortArrayWithDuplicates) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    heapsort(arr);
    EXPECT_EQ(arr, expected);
}

// Тесты для PriorityQueue
class PriorityQueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        pq = new PriorityQueue<std::string, int>(true);
    }
    
    void TearDown() override {
        delete pq;
    }
    
    PriorityQueue<std::string, int>* pq;
};

TEST_F(PriorityQueueTest, EnqueueAndDequeue) {
    pq->enqueue("task1", 3);
    pq->enqueue("task2", 1);
    pq->enqueue("task3", 2);
    
    EXPECT_EQ(pq->size(), 3);
    EXPECT_EQ(pq->dequeue(), "task2");
    EXPECT_EQ(pq->dequeue(), "task3");
    EXPECT_EQ(pq->dequeue(), "task1");
    EXPECT_TRUE(pq->isEmpty());
}

TEST_F(PriorityQueueTest, Peek) {
    pq->enqueue("high", 1);
    pq->enqueue("low", 5);
    pq->enqueue("medium", 3);
    
    EXPECT_EQ(pq->peek(), "high");
    EXPECT_EQ(pq->size(), 3);
    EXPECT_EQ(pq->dequeue(), "high");
    EXPECT_EQ(pq->peek(), "medium");
}

TEST_F(PriorityQueueTest, MaxPriorityQueue) {
    PriorityQueue<std::string, int> max_pq(false);
    
    max_pq.enqueue("low", 1);
    max_pq.enqueue("high", 5);
    max_pq.enqueue("medium", 3);
    
    EXPECT_EQ(max_pq.dequeue(), "high");
    EXPECT_EQ(max_pq.dequeue(), "medium");
    EXPECT_EQ(max_pq.dequeue(), "low");
}

TEST_F(PriorityQueueTest, MultipleElementsSamePriority) {
    pq->enqueue("task1", 2);
    pq->enqueue("task2", 2);
    pq->enqueue("task3", 2);
    
    EXPECT_EQ(pq->size(), 3);
    std::vector<std::string> extracted;
    while (!pq->isEmpty()) {
        extracted.push_back(pq->dequeue());
    }
    
    EXPECT_EQ(extracted.size(), 3);
    EXPECT_TRUE(std::find(extracted.begin(), extracted.end(), "task1") != extracted.end());
    EXPECT_TRUE(std::find(extracted.begin(), extracted.end(), "task2") != extracted.end());
    EXPECT_TRUE(std::find(extracted.begin(), extracted.end(), "task3") != extracted.end());
}

