#include "test_framework/generic_test.h"
#include <iostream>
#include <climits>

int SquareRoot(int k) {
  int l = 0, r = k;
  while (l <= r) {
    int m = l + (r - l)/2;
    if (m > 0 && (m > INT_MAX/m || m * m > k))
      r = m - 1;
    else if (m * m <= k)
      l = m + 1;
  }

  return l - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
