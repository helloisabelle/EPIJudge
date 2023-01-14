#include "test_framework/generic_test.h"
#include <iostream>
#include <utility>
#include <vector>
//

void inverse(vector<int> v) {

  for (int i = 0; i < size; i++) {

    for (int j = 0; j < size; j++) {

      if (arr[j] == i) {
        v[i] = j;
        break;
      }
    }
  }
  for (int i = 0; i < v.size(); i++) {
    //2 should be at index 3v[v[i]]
    int j = i;
    while ()
    int val = v[v[j]];
    int index = v[j];
    v[v[j]] = j;
    j = index;

  }
  // TODO - you fill in here.
  return (x&(x-1)) + (x^(x-1));
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
  return 0;
}
