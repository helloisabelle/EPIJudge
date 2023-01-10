#include "test_framework/generic_test.h"
#include <cmath>
#include <string>
bool IsPalindromeNumber(int x) {
  // TODO - you fill in here.

//  std::string s = std::to_string(x);
//  for (int i = 0, j = s.size() - 1; i != j && i < s.size() - 1 && j >= 0; i++, j--) {
//    if (s[i] != s[j]) return false;
//  }
  if (x <= 0) return x == 0;
  int size = trunc(log10(x)) + 1;

  int msd_mask = pow(10, size - 1);
  for (int i = 0; i < (size / 2); i++) {
    // if msd != lsd
    if (x / msd_mask != x % 10) {
      return false;
    }

    // remove msd
    x %= msd_mask;
    // remove lsd
    x /= 10;
    // shorten mask
    msd_mask /= 100;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
