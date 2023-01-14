#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"

using std::swap;
using std::vector;

void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {

//    vector<int>& A = *A_ptr;
//    for (int i = 0; i < A.size(); i++) {
//      int ind = i;
//      while (perm[ind] >= 0) {
//        swap(A[ind], A[perm[ind]]);
//        ind = perm[ind];
//        perm[ind] -= A.size();
//      }
//    }
    vector<int>& A = *A_ptr;
    for (int i = 0; i < A.size(); i++) {
      int ind = perm[i];
      while (ind < i) {
        ind = perm[ind];
      }
      swap(A[i], A[ind]);
    }
}

vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
