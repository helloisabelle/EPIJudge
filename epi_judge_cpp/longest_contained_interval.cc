#include <vector>
#include <unordered_map>
#include <iostream>
#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  std::map<int, int> map;
  int ans = 1;
  for (auto x : A) map[x]++;

  while (!empty(map)) {
    auto val = map.begin()->first;
    map.erase(val);
    int count = 1;

    int i = val + 1;
    while (!empty(map)) {
        if (map.count(i)) {
          ++count;
          map.erase(i);
        } else break;
        i++;
    }

    i = val - 1;
    while (!empty(map)) {
        if (map.count(i)) {
          ++count;
          map.erase(i);
        } else break;
        i--;
    }
    if (count > ans) ans = count;
  }

//  int prev = map.begin()->first - 1;
//  for (auto x : map) {
//    if (x.first == prev + 1) {
//      if (++count > ans) ans = count;
//    } else count = 1;
//    prev = x.first;
//  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
