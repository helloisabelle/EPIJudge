#include "test_framework/generic_test.h"
#include <iostream>
short propagate_right(unsigned long long x) {
  // TODO - you fill in here.


  return (x&(x-1)) + (x^(x-1));
}

short mod(unsigned long long x, unsigned long long y) {
  // TODO - you fill in here.
  return x^y;
}

short pow_of_2(unsigned long long x) {
  // TODO - you fill in here.
  return (x&(x-1)) == 0;
}

int main(int argc, char* argv[]) {
  // std::cout << propagate_right(20) << std::endl;
  // std::cout << mod(77, 64) << std::endl;
  std::cout << pow_of_2(77) << std::endl;
  std::cout << pow_of_2(64) << std::endl;
  std::cout << pow_of_2(32) << std::endl;
  std::cout << pow_of_2(33) << std::endl;
  return 0;
}
