#include <memory>
#include <algorithm>
#include <iostream>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> helper(int i, int j, const vector<int>& preorder_sequence) {
  if (i == preorder_sequence.size() || j == preorder_sequence.size()) return nullptr;
  int l = i + 1, r = -1;
  for (int k = l; k <= j; k++) {
    if (preorder_sequence[k] > preorder_sequence[i]) {
      r = k;
      break;
    }
  }
  int l_size = j;
  unique_ptr<BstNode<int>> l_node = nullptr, r_node = nullptr;

  if (r != -1) {
    l_size = r - 1;
    r_node = helper(r, j, preorder_sequence);
  }

  if (preorder_sequence[i] > preorder_sequence[l]) {
    l_node = helper(l, l_size, preorder_sequence);
  }

  return std::make_unique<BstNode<int>>(
    BstNode<int>{preorder_sequence[i], std::move(l_node), std::move(r_node)}
  );
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int>& preorder_sequence) {
  return helper(0, preorder_sequence.size() - 1, preorder_sequence);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
