#include <memory>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using test_framework::BinaryTreeSerializationTrait;
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
  BinaryTreeNode<T>* next = nullptr;  // Populates this field.

  explicit BinaryTreeNode(T data) : data(data){};
};

void ConstructRightSiblingHelper(BinaryTreeNode<int>* left, BinaryTreeNode<int>* right) {
  if (!left) return;
  else {
    left->next = right;
    ConstructRightSiblingHelper(left->left.get(), left->right.get());
    ConstructRightSiblingHelper(left->right.get(), right->left.get());
    ConstructRightSiblingHelper(right->left.get(), right->right.get());
  }
  return;
}

void ConstructRightSiblingHelper2(BinaryTreeNode<int>* node) {
  while (node) {
    node->left->next = node->right.get();

    // set curr's right child to curr's next left child
    if (node->next) node->right->next = node->next->left.get();

    // go along the nodes in this level
    node = node->next;
  }
}

void ConstructRightSibling(BinaryTreeNode<int>* tree) {
//  if (!tree) return;
//  ConstructRightSiblingHelper(tree->left.get(), tree->right.get());
  while (tree && tree->left) {
    ConstructRightSiblingHelper2(tree);
    tree = tree->left.get();
  }
  return;
}

namespace test_framework {
template <>
struct SerializationTrait<unique_ptr<BinaryTreeNode<int>>>
    : BinaryTreeSerializationTrait<unique_ptr<BinaryTreeNode<int>>, false> {};
}  // namespace test_framework

std::vector<std::vector<int>> ConstructRightSiblingWrapper(
    TimedExecutor& executor, unique_ptr<BinaryTreeNode<int>>& tree) {
  executor.Run([&] { ConstructRightSibling(tree.get()); });

  std::vector<std::vector<int>> result;
  auto level_start = tree.get();
  while (level_start) {
    result.emplace_back();
    auto level_iter = level_start;
    while (level_iter) {
      result.back().push_back(level_iter->data);
      level_iter = level_iter->next;
    }
    level_start = level_start->left.get();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "tree_right_sibling.cc", "tree_right_sibling.tsv",
      &ConstructRightSiblingWrapper, DefaultComparator{}, param_names);
}
