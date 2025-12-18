#pragma once

#include <memory>
#include <vector>
#include <stack>

template<typename T>
class TreeNode {
public:
    T data;                                      // Данные узла
    std::unique_ptr<TreeNode<T>> left;            // Левый потомок
    std::unique_ptr<TreeNode<T>> right;           // Правый потомок
    
    explicit TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinarySearchTree {
private:
    std::unique_ptr<TreeNode<T>> root;            // Корень дерева
    
    // Вспомогательные рекурсивные функции
    TreeNode<T>* insert(TreeNode<T>* node, const T& value);
    TreeNode<T>* search(TreeNode<T>* node, const T& value) const;
    TreeNode<T>* remove(TreeNode<T>* node, const T& value);
    TreeNode<T>* findMinNode(TreeNode<T>* node) const;
    TreeNode<T>* findMaxNode(TreeNode<T>* node) const;
    bool isValidBST(TreeNode<T>* node, const T* min_val, const T* max_val) const;
    int height(TreeNode<T>* node) const;
    void visualize(TreeNode<T>* node, int depth) const;
    
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    
    // Основные операции
    void insert(const T& value);                 // Вставка элемента
    bool search(const T& value) const;            // Поиск элемента
    void remove(const T& value);                  // Удаление элемента
    
    // Дополнительные методы
    T findMin() const;                            // Поиск минимума
    T findMax() const;                            // Поиск максимума
    int height() const;                            // Высота дерева
    bool isValidBST() const;                       // Проверка корректности BST
    void visualize() const;                         // Визуализация дерева
    bool isEmpty() const { return root == nullptr; } // Проверка на пустоту
    
    // Получение корня для функций обхода
    TreeNode<T>* getRoot() const { return root.get(); }
};