#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <list>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
    std::list<int> loc;
    std::unordered_map<string, std::list<int>::iterator> map;
    Subarray res = {-1, -1};

    for (auto w : keywords) map[w] = loc.end();

    auto it = paragraph.begin();
    int i = 0;

    while (i != size(paragraph)) {
      string s = *it++;
      if (map.find(s) != map.end()) {
        if (map[s] == loc.end()) loc.erase(map[s]);

        loc.emplace_back(i);
        map[s] = --loc.end();

        if (size(loc) == size(keywords)) {
          if (res.start + res.end < 0 || res.end - res.start > i - loc.front())
            res = {loc.front(), i};
        }
      }
      ++i;
    }

//  std::unordered_map<string, int> map;
//  int still_looking = keywords.size();
//  Subarray res = {-1, -1};
//
//  for (auto w : keywords) ++map[w];
//
//  for (int l = 0, r = 0; r < paragraph.size(); ++r) {
//    if (keywords.find(paragraph[r]) != keywords.end() && map[paragraph[r]]-- > 0) {
//      --still_looking;
//    }
//
//    while (still_looking == 0) {
//      if (res.start + res.end < 0 || res.end - res.start > r - l) res = {l, r};
//      if (keywords.count(paragraph[l]) && ++map[paragraph[l]] > 0) {
//        ++still_looking;
//      }
//      ++l;
//    }
//  }
//
  return res;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
