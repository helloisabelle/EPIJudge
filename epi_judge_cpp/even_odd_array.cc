#include <set>
#include <vector>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void EvenOdd(vector<int>* A_ptr) {

  vector<int> &v = *A_ptr;

  int next_even = 0, next_odd = v.size() - 1;

//  while (next_even < next_odd) {
//    if (v[next_even] % 2 == 0) {
//      next_even++;
//    } else {
//        std::swap(v[next_even], v[next_odd--]);
//    }
//  }

  int first_odd = -1;

  for (int i = 0; i < v.size(); i++) {
    if (first_odd == -1 && (v[i] & 1) != 0) // odd
        first_odd = i;
    else if (first_odd != -1 && (v[i] & 1) == 0)
        std::swap(v[first_odd++], v[i]);
  }

  return;
}
void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
