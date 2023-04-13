#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
  vector<int> dp(size(A), 1);
  int ans = 1;
  for (int i = 1; i < size(A); ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (A[j] <= A[i] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        ans = std::max(ans, dp[i]);
      }
    }
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
                         "longest_nondecreasing_subsequence.tsv",
                         &LongestNondecreasingSubsequenceLength,
                         DefaultComparator{}, param_names);
}
