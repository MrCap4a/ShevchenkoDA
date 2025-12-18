#include "../include/binary_search_tree.h"
#include <iostream>
#include <limits>
#include <algorithm>

template<typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>* node, const T& value) {
    // Базовый случай - достигли места для вставки
    if (node == nullptr) {
        return new TreeNode<T>(value);
    }
    
    // Рекурсивный спуск в зависимости от значения
    if (value < node->data) {
        node->left.reset(insert(node->left.release(), value));
    } else if (value > node->data) {
        node->right.reset(insert(node->right.release(), value));
    }
    
    return node;
}

template<typename T>
void BinarySearchTree<T>::insert(const T& value) {
    // Сложность: в среднем O(log n), в худшем O(n)
    root.reset(insert(root.release(), value));
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::search(TreeNode<T>* node, const T& value) const {
    // Базовые случаи: дерево пусто или значение найдено
    if (node == nullptr || node->data == value) {
        return node;
    }
    
    // Рекурсивный поиск в соответствующем поддереве
    if (value < node->data) {
        return search(node->left.get(), value);
    } else {
        return search(node->right.get(), value);
    }
}

template<typename T>
bool BinarySearchTree<T>::search(const T& value) const {
    // Сложность: в среднем O(log n), в худшем O(n)
    return search(root.get(), value) != nullptr;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::findMinNode(TreeNode<T>* node) const {
    while (node && node->left) {
        node = node->left.get();
    }
    return node;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::findMaxNode(TreeNode<T>* node) const {
    while (node && node->right) {
        node = node->right.get();
    }
    return node;
}

template<typename T>
T BinarySearchTree<T>::findMin() const {
    // Complexity: O(log n) for balanced tree, O(n) for degenerate tree
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    return findMinNode(root.get())->data;
}

template<typename T>
T BinarySearchTree<T>::findMax() const {
    // Complexity: O(log n) for balanced tree, O(n) for degenerate tree
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    return findMaxNode(root.get())->data;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::remove(TreeNode<T>* node, const T& value) {
    if (node == nullptr) {
        return node;
    }
    
    if (value < node->data) {
        node->left.reset(remove(node->left.release(), value));
    } else if (value > node->data) {
        node->right.reset(remove(node->right.release(), value));
    } else {
        // Node with only one child or no child
        if (node->left == nullptr) {
            return node->right.release();
        } else if (node->right == nullptr) {
            return node->left.release();
        }
        
        // Node with two children: Get the inorder successor
        TreeNode<T>* temp = findMinNode(node->right.get());
        node->data = temp->data;
        node->right.reset(remove(node->right.release(), temp->data));
    }
    
    return node;
}

template<typename T>
void BinarySearchTree<T>::remove(const T& value) {
    // Complexity: Average O(log n), Worst O(n)
    root.reset(remove(root.release(), value));
}

template<typename T>
bool BinarySearchTree<T>::isValidBST(TreeNode<T>* node, const T* min_val, const T* max_val) const {
    if (node == nullptr) {
        return true;
    }
    
    if ((min_val && node->data <= *min_val) || (max_val && node->data >= *max_val)) {
        return false;
    }
    
    return isValidBST(node->left.get(), min_val, &node->data) &&
           isValidBST(node->right.get(), &node->data, max_val);
}

template<typename T>
bool BinarySearchTree<T>::isValidBST() const {
    return isValidBST(root.get(), nullptr, nullptr);
}

template<typename T>
int BinarySearchTree<T>::height(TreeNode<T>* node) const {
    if (node == nullptr) {
        return -1;
    }
    
    return 1 + std::max(height(node->left.get()), height(node->right.get()));
}

template<typename T>
int BinarySearchTree<T>::height() const {
    return height(root.get());
}

template<typename T>
void BinarySearchTree<T>::visualize(TreeNode<T>* node, int depth) const {
    if (node == nullptr) {
        return;
    }
    
    visualize(node->right.get(), depth + 1);
    
    for (int i = 0; i < depth; ++i) {
        std::cout << "    ";
    }
    std::cout << node->data << std::endl;
    
    visualize(node->left.get(), depth + 1);
}

template<typename T>
void BinarySearchTree<T>::visualize() const {
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    
    visualize(root.get(), 0);
}

// Explicit template instantiations
template class BinarySearchTree<int>;
template class BinarySearchTree<double>;
template class BinarySearchTree<float>;