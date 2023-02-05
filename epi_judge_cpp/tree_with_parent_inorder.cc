#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  BinaryTreeNode<int>* curr = tree.get(), *prev = nullptr, *next = nullptr;
  vector<int> ans;
  while (curr) {
    if (curr->parent == prev) {
      // we just finished root
      // curr is the right
      if (curr->left) next = curr->left.get();
      else {
        ans.emplace_back(curr->data);
        next = curr->right.get() ? curr->right.get() : curr->parent;
      }

    } else if (curr->left.get() == prev){
      // we just finished left
      // curr is the root
      ans.emplace_back(curr->data);
      if (curr->right) next = curr->right.get();
      else next = curr->parent;
    } else if (curr->right.get() == prev){
      // we just finished right
      // finished this subtree
      next = curr->parent;
    }
    prev = curr;
    curr = next;
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
