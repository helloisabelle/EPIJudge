#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include <unordered_map>

using std::vector;

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, size_t p_start, size_t p_end, size_t i_start, size_t i_end, std::unordered_map<int, size_t> map) {

  if (p_start >= p_end || i_start >= i_end) return nullptr;
  size_t root_inorder = map[preorder[p_start]]; // what index is p_start at in inorder
  size_t left_tree_size = root_inorder - i_start;

  return std::make_unique<BinaryTreeNode<int>>(
    BinaryTreeNode<int>{
      preorder[p_start],
      // left root is at p_start + 1
      // inorder subtree is from i_start to root_inorder
      BinaryTreeFromPreorderInorderHelper(preorder, p_start + 1, p_start + 1 + left_tree_size, i_start, root_inorder, map),
      // right root is at p_start + 1 + left_tree_size
      // inorder subtree is from root_inorder + 1 to i_end
      BinaryTreeFromPreorderInorderHelper(preorder, p_start + 1 + left_tree_size, p_end, root_inorder + 1, i_end, map)
    }
  );
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {

  std::unordered_map<int, size_t> map;
  for (size_t i = 0; i < inorder.size(); ++i) {
   map[inorder[i]] = i;
  }
  return BinaryTreeFromPreorderInorderHelper(preorder, 0, preorder.size(), 0, preorder.size(), map);
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
