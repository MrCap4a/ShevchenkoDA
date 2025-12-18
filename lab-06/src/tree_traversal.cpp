#include "../include/tree_traversal.h"
#include <iostream>

template <typename T>
std::vector<T> TreeTraversal<T>::inOrder(TreeNode<T> *node) {
  // Симметричный обход: левый-корень-правый
  std::vector<T> result;
  if (node == nullptr) {
    return result;
  }

  // Обход левого поддерева
  auto leftResult = inOrder(node->left.get());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  // Посещение корня
  result.push_back(node->data);

  // Обход правого поддерева
  auto rightResult = inOrder(node->right.get());
  result.insert(result.end(), rightResult.begin(), rightResult.end());

  return result;
}

template <typename T>
std::vector<T> TreeTraversal<T>::preOrder(TreeNode<T> *node) {
  std::vector<T> result;
  if (node == nullptr) {
    return result;
  }

  result.push_back(node->data);

  auto leftResult = preOrder(node->left.get());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  auto rightResult = preOrder(node->right.get());
  result.insert(result.end(), rightResult.begin(), rightResult.end());

  return result;
}

template <typename T>
std::vector<T> TreeTraversal<T>::postOrder(TreeNode<T> *node) {
  std::vector<T> result;
  if (node == nullptr) {
    return result;
  }

  auto leftResult = postOrder(node->left.get());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  auto rightResult = postOrder(node->right.get());
  result.insert(result.end(), rightResult.begin(), rightResult.end());

  result.push_back(node->data);

  return result;
}

template <typename T>
std::vector<T> TreeTraversal<T>::inOrderIterative(TreeNode<T> *node) {
  std::vector<T> result;
  std::stack<TreeNode<T> *> stack;
  TreeNode<T> *current = node;

  while (current != nullptr || !stack.empty()) {
    while (current != nullptr) {
      stack.push(current);
      current = current->left.get();
    }

    current = stack.top();
    stack.pop();
    result.push_back(current->data);
    current = current->right.get();
  }

  return result;
}

template <typename T>
std::vector<T> TreeTraversal<T>::preOrderIterative(TreeNode<T> *node) {
  std::vector<T> result;
  if (node == nullptr) {
    return result;
  }

  std::stack<TreeNode<T> *> stack;
  stack.push(node);

  while (!stack.empty()) {
    TreeNode<T> *current = stack.top();
    stack.pop();
    result.push_back(current->data);

    if (current->right) {
      stack.push(current->right.get());
    }
    if (current->left) {
      stack.push(current->left.get());
    }
  }

  return result;
}

template <typename T>
std::vector<T> TreeTraversal<T>::postOrderIterative(TreeNode<T> *node) {
  std::vector<T> result;
  if (node == nullptr) {
    return result;
  }

  std::stack<TreeNode<T> *> stack1, stack2;
  stack1.push(node);

  while (!stack1.empty()) {
    TreeNode<T> *current = stack1.top();
    stack1.pop();
    stack2.push(current);

    if (current->left) {
      stack1.push(current->left.get());
    }
    if (current->right) {
      stack1.push(current->right.get());
    }
  }

  while (!stack2.empty()) {
    result.push_back(stack2.top()->data);
    stack2.pop();
  }

  return result;
}

template <typename T>
void TreeTraversal<T>::printVector(const std::vector<T> &vec) {
  for (const auto &item : vec) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

template class TreeTraversal<int>;
template class TreeTraversal<double>;
template class TreeTraversal<float>;
