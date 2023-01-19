#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  int i = 0, j = s.size() - 1;
  while (i < j) {
    char c1 = s[i], c2 = s[j];
    int n1 = s[i] - '0', n2 = s[j] - '0';
    while (i < j && !((c1 >= 'A' && c1 <= 'Z')  || (c1 >= 'a' && c1 <= 'z') || (n1 >= 0 && n1 <= 9))) {
      c1 = s[++i];
      n1 = s[i] - '0';
    }
    while (i < j && !((c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z') || (n2 >= 0 && n2 <= 9))) {
      c2 = s[--j];
      n2 = s[j] - '0';
    }
    if (std::tolower(c1) != std::tolower(c2) && n1 != n2) return false;
    i++, j--;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
