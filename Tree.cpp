#include "Tree.h"
#include <stdexcept>

struct Tree::Node {
  std::string value;
  uint64_t size = 1;
  int height = 1;
  Node* left = nullptr;
  Node* right = nullptr;
  //
  explicit Node(const std::string& str) : value(str) {}
  //
  ~Node() {
    delete left;
    delete right;
  }
};

Tree::~Tree() {
  delete _root;
}

void Tree::insert(const std::string& str) {
  _root = insert(_root, str);
}

void Tree::erase(uint64_t index) {
  if (index >= getSize(_root)) {
    throw std::out_of_range{"index out of range"};
  }
  _root = remove(_root, index);
}

const std::string& Tree::get(uint64_t index) const {
  if (index >= getSize(_root)) {
    throw std::out_of_range{"index out of range"};
  }
  return findByIndex(_root, index)->value;
}

uint64_t Tree::size() const {
  return getSize(_root);
}

int Tree::height() const {
  return getHeight(_root);
}

Tree::Node* Tree::insert(Node* p, const std::string& str) {
  if (p == nullptr) {
    return new Node(str);
  }
  auto comp = p->value.compare(str);
  if (comp > 0) {
    p->left = insert(p->left, str);
  } else if (comp < 0) {
    p->right = insert(p->right, str);
  } else {
    return p;
  }
  return rebalance(p);
}

Tree::Node* Tree::remove(Node* p, uint64_t index) {
  auto lsize = getSize(p->left);
  if (lsize > index) {
    p->left = remove(p->left, index);
  } else if (lsize < index) {
    p->right = remove(p->right, index - lsize - 1);
  } else {
    auto* l = p->left;
    auto* r = p->right;
    p->left = nullptr;
    p->right = nullptr;
    delete p;
    if (r == nullptr) {
      return l;
    }
    auto* rmin = findMin(r);
    rmin->right = replaceMin(r);
    rmin->left = l;
    return rebalance(rmin);
  }
  return rebalance(p);
}

Tree::Node* Tree::findByIndex(Node* p, uint64_t index) {
  auto lsize = getSize(p->left);
  if (lsize > index) {
    return findByIndex(p->left, index);
  } else if (lsize < index) {
    return findByIndex(p->right, index - lsize - 1);
  }
  return p;
}

Tree::Node* Tree::findMin(Node* p) {
  return p->left != nullptr ? findMin(p->left) : p;
}

Tree::Node* Tree::replaceMin(Node* p) {
  if (p->left == nullptr) {
    return p->right;
  }
  p->left = replaceMin(p->left);
  return rebalance(p);
}

Tree::Node* Tree::rebalance(Node* p) {
  updateSizeAndHeight(p);
  int balance = getBalance(p);
  if (balance > 1) {
    if (getBalance(p->right) < 0) {
      p->right = rotateRight(p->right);
    }
    return rotateLeft(p);
  } else if (balance < -1) {
    if (getBalance(p->left) > 0) {
      p->left = rotateLeft(p->left);
    }
    return rotateRight(p);
  }
  return p;
}

Tree::Node* Tree::rotateLeft(Tree::Node* p) {
  Node* q = p->right;
  p->right = q->left;
  q->left = p;
  updateSizeAndHeight(p);
  updateSizeAndHeight(q);
  return q;
}

Tree::Node* Tree::rotateRight(Tree::Node* p) {
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  updateSizeAndHeight(p);
  updateSizeAndHeight(q);
  return q;
}

int Tree::getBalance(Node* p) {
  return getHeight(p->right) - getHeight(p->left);
}

int Tree::getHeight(Node* p) {
  return p != nullptr ? p->height : 0;
}

uint64_t Tree::getSize(Node* p) {
  return p != nullptr ? p->size : 0;
}

void Tree::updateSizeAndHeight(Node* p) {
  int hmax = 0;
  p->size = 1;
  if (p->left != nullptr) {
    p->size += p->left->size;
    hmax = p->left->height;
  }
  if (p->right != nullptr) {
    p->size += p->right->size;
    if (hmax < p->right->height) {
      hmax = p->right->height;
    }
  }
  p->height = 1 + hmax;
}
