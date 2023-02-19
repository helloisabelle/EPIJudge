#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  std::unordered_map<char, int> map;
  int count = 0;

  for (auto x : s) map[x]++;

  for (auto x : map) {
    if (x.second % 2 != 0 && count == 0) count++;
    else if (x.second % 2 != 0) return false;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
