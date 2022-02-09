#ifndef TEST_TREE_H
#define TEST_TREE_H

#include <cstdint>
#include <string>

/**
 * Order statistic AVL tree
 */
class Tree {
 public:
  Tree() = default;
  ~Tree();

  void insert(const std::string& str);
  void erase(uint64_t index);
  const std::string& get(uint64_t index) const;

  uint64_t size() const;
  int height() const;

 private:
  struct Node;
  Node* _root = nullptr;

  static Node* insert(Node* p, const std::string& str);
  static Node* remove(Node* p, uint64_t index);
  static Node* findByIndex(Node* p, uint64_t index);
  static Node* findMin(Node* p);
  static Node* replaceMin(Node* p);
  static Node* rebalance(Node* p);
  static Node* rotateLeft(Node* p);
  static Node* rotateRight(Node* p);
  static int getBalance(Node* p);
  static int getHeight(Node* p);
  static uint64_t getSize(Node* p);
  static void updateSizeAndHeight(Node* p);
};

#endif // TEST_TREE_H
