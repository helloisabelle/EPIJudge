#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void helper(vector<int> res, const vector<int> candidates, vector<vector<int>>& ans) {
  ans.emplace_back(res);
  for (int i = 0; i < size(candidates); ++i) {
    res.emplace_back(candidates[i]);
    helper(res, {candidates.begin() + i + 1, candidates.end()}, ans);
    res.pop_back();
  }
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  vector<vector<int>> ans;
  helper({}, input_set, ans);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
