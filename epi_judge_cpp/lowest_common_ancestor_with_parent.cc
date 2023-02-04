#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <unordered_map>
#include <iostream>

int getDepth(BinaryTreeNode<int>* node0, int depth) {
  if (!node0) return depth;
  else return getDepth(node0->parent, depth + 1);
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {

  BinaryTreeNode<int>* curr0 = node0.get();
  BinaryTreeNode<int>* curr1 = node1.get();

  int x = getDepth(curr0, 0);
  int y = getDepth(curr1, 0);

  if (x > y) {
    while (x-- != y) curr0 = curr0->parent;
  } else if (y > x) {
    while (y-- != x) curr1 = curr1->parent;
  }

  while (curr0 && curr1) {
    if (curr0 == curr1) return curr0;
    curr0 = curr0->parent;
    curr1 = curr1->parent;
  }

  return node0.get();
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
