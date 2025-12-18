#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../include/binary_search_tree.h"

class BinarySearchTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        tree = new BinarySearchTree<int>();
    }
    
    void TearDown() override {
        delete tree;
    }
    
    BinarySearchTree<int>* tree;
};

TEST_F(BinarySearchTreeTest, InsertSingleElement) {
    tree->insert(5);
    EXPECT_TRUE(tree->search(5));
    EXPECT_FALSE(tree->search(1));
}

TEST_F(BinarySearchTreeTest, InsertMultipleElements) {
    std::vector<int> elements = {5, 3, 7, 2, 4, 6, 8};
    
    for (int elem : elements) {
        tree->insert(elem);
    }
    
    for (int elem : elements) {
        EXPECT_TRUE(tree->search(elem)) << "Element " << elem << " should be found";
    }
    
    EXPECT_FALSE(tree->search(1));
    EXPECT_FALSE(tree->search(9));
}

TEST_F(BinarySearchTreeTest, SearchEmptyTree) {
    EXPECT_FALSE(tree->search(5));
}

TEST_F(BinarySearchTreeTest, FindMinAndMax) {
    tree->insert(5);
    tree->insert(3);
    tree->insert(7);
    tree->insert(2);
    tree->insert(8);
    
    EXPECT_EQ(tree->findMin(), 2);
    EXPECT_EQ(tree->findMax(), 8);
}

TEST_F(BinarySearchTreeTest, FindMinAndMaxSingleElement) {
    tree->insert(5);
    
    EXPECT_EQ(tree->findMin(), 5);
    EXPECT_EQ(tree->findMax(), 5);
}

TEST_F(BinarySearchTreeTest, FindMinAndMaxEmptyTree) {
    EXPECT_THROW(tree->findMin(), std::runtime_error);
    EXPECT_THROW(tree->findMax(), std::runtime_error);
}

TEST_F(BinarySearchTreeTest, RemoveLeaf) {
    tree->insert(5);
    tree->insert(3);
    tree->insert(7);
    
    tree->remove(3);
    
    EXPECT_FALSE(tree->search(3));
    EXPECT_TRUE(tree->search(5));
    EXPECT_TRUE(tree->search(7));
}

TEST_F(BinarySearchTreeTest, Height) {
    EXPECT_EQ(tree->height(), -1);
    
    tree->insert(5);
    EXPECT_EQ(tree->height(), 0);
    
    tree->insert(3);
    EXPECT_EQ(tree->height(), 1);
    
    tree->insert(7);
    EXPECT_EQ(tree->height(), 1);
    
    tree->insert(2);
    EXPECT_EQ(tree->height(), 2);
}

TEST_F(BinarySearchTreeTest, IsValidBST) {
    EXPECT_TRUE(tree->isValidBST());
    
    tree->insert(5);
    tree->insert(3);
    tree->insert(7);
    tree->insert(2);
    tree->insert(4);
    tree->insert(6);
    tree->insert(8);
    
    EXPECT_TRUE(tree->isValidBST());
}

TEST_F(BinarySearchTreeTest, DegenerateTree) {
    for (int i = 1; i <= 10; ++i) {
        tree->insert(i);
    }
    
    EXPECT_EQ(tree->height(), 9);
    
    for (int i = 1; i <= 10; ++i) {
        EXPECT_TRUE(tree->search(i)) << "Element " << i << " should be found";
    }
}

TEST_F(BinarySearchTreeTest, BalancedTree) {
    std::vector<int> elements = {5, 3, 7, 2, 4, 6, 8, 1, 9};
    
    for (int elem : elements) {
        tree->insert(elem);
    }
    
    EXPECT_LT(tree->height(), 5);
    
    for (int elem : elements) {
        EXPECT_TRUE(tree->search(elem)) << "Element " << elem << " should be found";
    }
}