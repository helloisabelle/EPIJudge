#include <vector>
#include <unordered_set>
#include <iostream>
#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  std::unordered_set<int> set;
  int ans = 1;
  for (auto x : A) set.emplace(x);

  while (!empty(set)) {
    auto val = *set.begin();
    set.erase(val);
    int count = 1;

    int i = val + 1;
    while (set.count(i)) {
        ++count;
        set.erase(i);
        i++;
    }

    i = val - 1;
    while (set.count(i)) {
        ++count;
        set.erase(i);
        i--;
    }
    if (count > ans) ans = count;
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
