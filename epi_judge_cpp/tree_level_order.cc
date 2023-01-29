#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void traverse(const unique_ptr<BinaryTreeNode<int>>& tree, int depth, vector<vector<int>>& ans) {
  if (tree == nullptr) return;
  if (ans.size() <= depth) ans.push_back({});
  ans[depth].emplace_back(tree->data);
  traverse(tree->left, depth + 1, ans);
  traverse(tree->right, depth + 1, ans);
}

vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<vector<int>> ans;
  traverse(tree, 0, ans);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
