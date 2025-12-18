#pragma once

#include "binary_search_tree.h"
#include <vector>
#include <stack>

template<typename T>
class TreeTraversal {
public:
    // Recursive traversals
    static std::vector<T> inOrder(TreeNode<T>* node);
    static std::vector<T> preOrder(TreeNode<T>* node);
    static std::vector<T> postOrder(TreeNode<T>* node);
    
    // Iterative traversals
    static std::vector<T> inOrderIterative(TreeNode<T>* node);
    static std::vector<T> preOrderIterative(TreeNode<T>* node);
    static std::vector<T> postOrderIterative(TreeNode<T>* node);
    
    // Utility functions
    static void printVector(const std::vector<T>& vec);
};