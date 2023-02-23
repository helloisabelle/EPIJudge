#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

struct Obj {
  int index;
  int distance;
};

int FindNearestRepetition(const vector<string>& paragraph) {
  std::unordered_map<string, Obj> map;
  int ans = paragraph.size();

  for (int i = 0; i < paragraph.size(); i++) {
    auto it = map.find(paragraph[i]);
    if (it != map.end()) {
      int distance = i - it->second.index;
      if (distance < it->second.distance && distance < ans) {
        ans = distance;
        map[paragraph[i]] = Obj{i, distance};
      } else map[paragraph[i]] = Obj{i, it->second.distance};
    } else map[paragraph[i]] = Obj{i, static_cast<int>(paragraph.size())};
  }

  if (ans == paragraph.size()) return -1;
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
