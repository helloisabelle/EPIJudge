#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> helper(
    const vector<int>& A, int l, int r) {
  if (l > r) return nullptr;
  int m = l + (r - l)/2;
  return std::make_unique<BstNode<int>>(
    BstNode<int>{
      A[m],
      helper(A, l, m - 1),
      helper(A, m + 1, r)
    }
  );
}

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(
    const vector<int>& A) {
  return helper(A, 0, A.size() - 1);
}
int BuildMinHeightBSTFromSortedArrayWrapper(TimedExecutor& executor,
                                            const vector<int>& A) {
  auto result =
      executor.Run([&] { return BuildMinHeightBSTFromSortedArray(A); });

  if (test_framework::GenerateInorder(result) != A) {
    throw TestFailure("Result binary tree mismatches input array");
  }
  return test_framework::BinaryTreeHeight(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "bst_from_sorted_array.cc",
                         "bst_from_sorted_array.tsv",
                         &BuildMinHeightBSTFromSortedArrayWrapper,
                         DefaultComparator{}, param_names);
}
