#include <memory>
#include <vector>
#include <queue>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void helper(std::vector<int>& result, const unique_ptr<BstNode<int>>& tree, int k) {
  if (!tree) return;
  helper(result, tree->right, k);
  if (result.size() == k) return;
  result.emplace_back(tree->data);
  helper(result, tree->left, k);

}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  vector<int> ans;
  helper(ans, tree, k);
  return {ans.rbegin(), ans.rend()};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
