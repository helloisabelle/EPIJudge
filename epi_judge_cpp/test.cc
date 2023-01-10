#include "test_framework/generic_test.h"
#include <iostream>
#include <utility>
#include <vector>
//
bool isRectangle(std::vector<std::pair<int, int> >& v) {
  // TODO - you fill in here.
  if (v[0].first - v[1].first == v[2].first - v[3].first) {
    if (v[0].second - v[1].second == v[2].second - v[3].second) {
      return true;
    }
  } else if (v[1].first - v[2].first == v[0].first - v[3].first) {
    if (v[1].second - v[2].second == v[0].second - v[3].second) {
        return true;
    }
  }

  return false;
}

short propagate_right(unsigned long long x) {
  // TODO - you fill in here.


  return (x&(x-1)) + (x^(x-1));
}

short mod(unsigned long long x, unsigned long long y) {
  // TODO - you fill in here.
  return (x&(x-1));
}

short pow_of_2(unsigned long long x) {
  // TODO - you fill in here.
  return (x&(x-1)) == 0;
}

int main(int argc, char* argv[]) {
  // std::cout << propagate_right(20) << std::endl;
  // std::cout << mod(77, 64) << std::endl;
  std::vector<std::pair <int,int> > v{std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(0, 0), std::make_pair(1, 0)};
  std::cout << isRectangle(v) << std::endl;
  return 0;
}
