#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int add = 1;

  for (int i = A.size() - 1; i >= 0; i--) {
    int val = A[i] + add;
    if (val >= 10) {
     A[i] = 10 - val;
     add = 1;
    } else {
        A[i] = val;
        add = 0;
        break;
    }
  }

  if (add) A.emplace(A.begin(), 1);

  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
