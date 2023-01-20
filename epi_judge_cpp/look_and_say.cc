#include <string>
#include <cmath>
#include <iostream>
#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  string ans = "", prev = "1";
  int count = 1;

  if (n == 1) return "1";

  while (count < n) {
    ans = "";
    char start = '-';
    int repeat = 0, index = prev.size() - 1;
    std::reverse(prev.begin(), prev.end());
    while (prev.size()) {
      char comp = prev[index--];
      if (comp != start) {
        if (start != '-') {
          ans.push_back(repeat + '0');
          ans.push_back(start);
        }
        start = comp;
        repeat = 1;
      } else repeat++;
      prev.pop_back();
    }
    ans.push_back(repeat + '0');
    ans.push_back(start);
    count++;
    prev = ans;
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
