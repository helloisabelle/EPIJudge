#include <memory>
#include <cmath>
#include <climits>
#include <iostream>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

struct Obj {
  int min, max;
};

bool helper(const unique_ptr<BinaryTreeNode<int>>& tree, Obj* o) {
  if (!tree) return true;
  Obj& obj = *o;

  Obj* x = new Obj{INT_MAX, INT_MIN};
  Obj* x2 = new Obj{INT_MAX, INT_MIN};
  bool res = helper(tree->left, x);

  if (res == false) {
    return false;
  } else if ((x->min == INT_MAX && x->max == INT_MIN) || x->max <= tree->data) {
    bool res2= helper(tree->right, x2);
    if (res2 == false) {
      return false;
    } else if ((x2->min == INT_MAX && x2->max == INT_MIN) || x2->min >= tree->data) {
      obj.min = std::min(x->min, tree->data);
      obj.max = std::max(x2->max, tree->data);
      return true;
    } else return false;
  } else {
    return false;
  }

  delete x;
  delete x2;
}

bool inRange(const unique_ptr<BinaryTreeNode<int>>& tree, int high, int low) {
  if (!tree) return true;
  if (tree->data <= high && tree->data >= low) {
    return inRange(tree->left, tree->data, low) && inRange(tree->right, high, tree->data);
  }
  return false;
//  if (!tree) return true;
//  Obj* def = new Obj{tree->data, tree->data};
//  bool save = helper(tree, def);
//  delete def;
//  return save;
}

bool inOrder(const unique_ptr<BinaryTreeNode<int>>& tree, int& prev) {
  if (!tree) return true;
  if (inOrder(tree->left, prev) && tree->data >= prev) {
    prev = tree->data;
    return inOrder(tree->right, prev);
  }
  prev = tree->data;
  return false;
}

struct QueueEntry {
  const unique_ptr<BinaryTreeNode<int>>& node;
  int low, high;
};

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  std::queue<QueueEntry> q;
  q.emplace(QueueEntry{tree, INT_MIN, INT_MAX});
  while (!empty(q)) {
    auto curr = q.front();
    q.pop();
    if (!curr.node) continue;
    else if (curr.node->data <= curr.high && curr.node->data >= curr.low) {
      q.emplace(QueueEntry{curr.node->left, curr.low, curr.node->data});
      q.emplace(QueueEntry{curr.node->right, curr.node->data, curr.high});
    } else return false;
  }

  return true;
//  if (!tree) return true;
//  Obj* def = new Obj{tree->data, tree->data};
//  bool save = helper(tree, def);
//  delete def;
//  return save;
//  return inRange(tree, INT_MAX, INT_MIN);
//  int val = INT_MIN;
//  return inOrder(tree, val);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
