#include "../include/binary_search_tree.h"
#include "../include/tree_traversal.h"
#include <iostream>

int main() {
  BinarySearchTree<int> bst;

  std::cout << "\n1. Вставка элементов: 5, 3, 7, 2, 4, 6, 8" << std::endl;
  int elements[] = {5, 3, 7, 2, 4, 6, 8};
  for (int elem : elements) {
    bst.insert(elem);
  }

  std::cout << "\n2. Структура дерева (повернуто на 90 градусов):" << std::endl;
  bst.visualize();

  std::cout << "\n3. Обходы дерева:" << std::endl;
  auto root = bst.getRoot();

  std::cout << "   In-order (рекурсивный):   ";
  auto inorder = TreeTraversal<int>::inOrder(root);
  TreeTraversal<int>::printVector(inorder);

  std::cout << "   Pre-order (рекурсивный):  ";
  auto preorder = TreeTraversal<int>::preOrder(root);
  TreeTraversal<int>::printVector(preorder);

  std::cout << "   Post-order (рекурсивный): ";
  auto postorder = TreeTraversal<int>::postOrder(root);
  TreeTraversal<int>::printVector(postorder);

  std::cout << "   In-order (итеративный):   ";
  auto inorder_iter = TreeTraversal<int>::inOrderIterative(root);
  TreeTraversal<int>::printVector(inorder_iter);

  std::cout << "\n4. Операции поиска:" << std::endl;
  std::cout << "   Поиск 5: " << (bst.search(5) ? "Найден" : "Не найден")
            << std::endl;
  std::cout << "   Поиск 10: " << (bst.search(10) ? "Найден" : "Не найден")
            << std::endl;

  std::cout << "\n5. Свойства дерева:" << std::endl;
  std::cout << "   Минимум: " << bst.findMin() << std::endl;
  std::cout << "   Максимум: " << bst.findMax() << std::endl;
  std::cout << "   Высота: " << bst.height() << std::endl;
  std::cout << "   Корректное BST: " << (bst.isValidBST() ? "Да" : "Нет")
            << std::endl;

  std::cout << "\n6. Удаление элемента 3:" << std::endl;
  bst.remove(3);
  std::cout << "   Поиск 3: " << (bst.search(3) ? "Найден" : "Не найден")
            << std::endl;
  std::cout << "   In-order после удаления: ";
  auto inorder_after = TreeTraversal<int>::inOrder(bst.getRoot());
  TreeTraversal<int>::printVector(inorder_after);

  std::cout << "\n7. Структура дерева после удаления:" << std::endl;
  bst.visualize();

  return 0;
}
