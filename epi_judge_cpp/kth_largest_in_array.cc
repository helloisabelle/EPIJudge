#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;

int partition(vector<int>& v, int index, int start, int end) {
  int pivot_value = v[index];
  int new_pivot = r;
  int save = start;

  // save pivot val in start
  std::swap(v[index], v[start]);

  start++;

  while (start <= end) {
    if (v[start] > pivot_value) std::swap(v[start], v[end--]);
    else start++;
  }

  std::swap(v[save], v[start]);

  return start;
}


// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int l = 0, r = A.size() - 1;

  std::random_device rd;
  std::default_random_engine seed(rd());

n/2 * n/2

  while (l <= r) {
    int m = std::uniform_int_distribution<>{l, r}(seed);
    // int m = l + (r - l)/2; this works too
    int res = partition(A, index, l, r);
    if (res == A.size() - k)
      return A[res];
    else if (res < A.size() - k)
      l = res + 1;
    else r = res - 1;
  }

  return 0;
}

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
