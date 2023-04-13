#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
  // TODO - you fill in here.
  std::sort(begin(A), end(A));
//  std::unordered_map<int, bool> map;
//
//  for (auto x : A) map[x] = true;


  for (int i = 0; i < size(A); ++i) {
    int l = 0, r = size(A) - 1;
    while (l <= r) {
      if (t - (A[l] + A[r]) == A[i]) return true;
      else {
        if (A[l] + A[r] < t - A[i]) ++l;
        else --r;
      }
    }
  }






//  for (int i = 0; i < size(A); ++i) {
//    for (int j = 0; j < size(A); ++j) {
//      if (map.find(t - (A[i] + A[j])) != map.end()) return true;
//      else {
//
//      }
//    }
//  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
