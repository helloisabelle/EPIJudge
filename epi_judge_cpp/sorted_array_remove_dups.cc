#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  vector<int>& v = *A_ptr;
  if (v.size() <= 1) return v.size();

  int prev = v[0];
  int index = 1;

//  for (int i = 1; i < v.size(); i++) {
//    while (i < v.size() && v[i] == prev) {
//        i++;
//    }
//    else if (i < v.size()) {
//        v[index] = v[i];
//        prev = v[i];
//        index++;
//    }
//  }


  for (int i = 1; i < v.size(); i++) {
      if (v[i] != prev) {
          v[index++] = v[i];
          prev = v[i];
      }
  }

  // m=2
  // 1112222344

  return index;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
