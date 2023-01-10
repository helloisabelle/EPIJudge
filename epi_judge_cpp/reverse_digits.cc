#include "test_framework/generic_test.h"
#include <string>
#include <cmath>
#include <iostream>

long long Reverse(int x) {
  int neg = 1;
  if (x < 0) {
    neg *= -1;
    x *= -1;
  }

//  int r = x;
//  int size = 0;
//
//  while (r) {
//    r /= 10;
//    size++;
//  }
  int size = trunc(log10(x)) + 1;

  long long hun = pow(10, size - 1);
  long long curr = 0;
  long long ans = 0;

  while (hun) {
    long long copy = x;
    copy /= hun;
    ans += copy * pow(10, curr++);
    x -= hun * copy;
    hun /= 10;
  }

  return ans * neg;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
