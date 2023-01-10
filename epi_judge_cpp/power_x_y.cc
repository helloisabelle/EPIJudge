#include "test_framework/generic_test.h"

double Power(double x, int y) {
//  double ans = 0;
//
//  if (y < 0) {
//    y *= -1;
//    x = 1/x;
//  }
//
//  if (y == 0) {
//    return 1;
//  } else if (y == 1) {
//    return x;
//  }
//  else {
//    double half = Power(x, y/2);
//    return y % 2 == 0 ? half * half : half * half * x;
//  }
//    long long power = y;
//
//    if (y < 0) {
//      power *= -1;
//      x = 1/x;
//    }
//
//    for (int i = 0; i < power; i++) {
//      ans *= x;
//    }
//
//    return ans;

  double ans = 1;
  long long power = y;

  if (y < 0) {
    // reciprocal, set pow as positive
    power *= -1;
    x = 1/x;
  }

  while (power) {
    // if odd, for power this will be true at some point
    if (power & 1) {
     ans *= x;
    }
    x *= x;
    // div by 2
    power >>= 1;
  }

   return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
