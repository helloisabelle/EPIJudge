#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <cmath>
#include <iostream>

int getHeight(const unique_ptr<BinaryTreeNode<int>>& node, int depth) {
  if (!node || depth == -1) return depth;
  int x = getHeight(node->left, 0);
  if (x == -1) return -1;
  int y = getHeight(node->right, 0);
  if (x == -1 || y == -1 || (std::abs(x-y) > 1)) return -1;
  return 1 + std::max(x,y);
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return true;
  int x = getHeight(tree->left, 0);
  if (x == -1) return false;
  int y = getHeight(tree->right, 0);
  if (x == -1 || y == -1 || (std::abs(x-y) > 1)) return false;
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
