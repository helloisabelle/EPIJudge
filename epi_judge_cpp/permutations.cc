#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void helper2(int i, vector<int>& res, vector<vector<int>>& ans) {
  if (i == size(res) - 1) ans.emplace_back(res);
  else {
    for (int j = i; j < size(res); ++j) {
      std::swap(res[i], res[j]);
      helper2(i + 1, res, ans);
      std::swap(res[i], res[j]);
    }
  }
}

void helper(vector<int> res, vector<int> left, int n, vector<vector<int>>& ans) {
  if (size(res) == n) ans.emplace_back(res);
  else {
    for (int i = 0; i < size(left); ++i) {
      res.emplace_back(left[i]);
      vector<int> v(left);
      v.erase(v.begin() + i);
      helper(res, v, n, ans);
      res.pop_back();
    }
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  vector<vector<int>> ans;
  helper2(0, A, ans);
  //helper({}, A, size(A), ans);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
