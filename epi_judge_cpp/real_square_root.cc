#include "test_framework/generic_test.h"
#include <string>
#include <cmath>

int Compare(const double a, const double b);

double SquareRoot(double x) {
  double l = x, r = x;
  if (x < 1.0) r = 1.0;
  else l = 1.0;

  while (l <= r) {
    double m = l + (r - l) * 0.5;
    int res = Compare(m * m, x);
    if (res == 2) return m;
    else if (res == 1) r = m;
    else l = m;
  }

  return l;
}

int Compare(const double a, const double b) {
  double diff = (a - b) / std::max(std::abs(a), std::abs(b));
  if (diff < -std::numeric_limits<double>::epsilon()) return 0;
  else if (diff > std::numeric_limits<double>::epsilon()) return 1;
  else return 2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
