#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> ans;
  int i = 0, j = 0;
  while (i < A.size() && j < B.size()) {
    while (A[i] < B[j] && i < A.size()) ++i;
    while (A[i] > B[j] && j < B.size()) ++j;
    if (i < A.size() && j < B.size() && A[i] == B[j]) {
      int save = A[i];
      ans.push_back(save);
      while (A[i] == save) ++i;
      while (B[j] == save) ++j;
    }
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
