#include <memory>
#include <unordered_map>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;


BinaryTreeNode<int>* helper(BinaryTreeNode<int>* node0, BinaryTreeNode<int>* node1, std::unordered_map<BinaryTreeNode<int>*, int>& map) {
  if (node0) map[node0]++;
  if (node1) map[node1]++;
  if (map[node0] > 1) return node0;
  else if (map[node1] > 1) return node1;
  if (node0 && node1) return helper(node0->parent, node1->parent, map);
  else if (node0) return helper(node0->parent, node1, map);
  else return helper(node0, node1->parent, map);
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  std::unordered_map<BinaryTreeNode<int>*, int> map;

  BinaryTreeNode<int>* one = node0.get();
  BinaryTreeNode<int>* two = node1.get();

  return helper(one, two, map);
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
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
