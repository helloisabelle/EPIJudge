#include <vector>
#include <algorithm>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct DuplicateAndMissing {
  int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
//  int dup = 0, missing = -1;
//  vector<int> copy(A);
//  std::sort(copy.begin(), copy.end());
//  int prev = -1, count = 0;
//
//  for (int i = 0; i < copy.size(); i++) {
//    if (copy[i] == count) count++;
//    if (copy[i] == prev) dup = copy[i];
//    prev = copy[i];
//  }

  int first_xor = 0;

  for (int i = 0; i < A.size(); i++) {
    first_xor ^= A[i] ^ i;
  }

  int low = first_xor & ~(first_xor - 1);
  int second_xor = 0;
  
  for (int i = 0; i < A.size(); i++) {
    if (A[i] & low) second_xor ^= A[i];
    if (i & low) second_xor ^= i;
  }

  for (auto x : A)
    if (x == second_xor) return {second_xor, second_xor ^ first_xor};

  return {second_xor ^ first_xor, second_xor};
}

namespace test_framework {
template <>
struct SerializationTrait<DuplicateAndMissing>
    : UserSerTrait<DuplicateAndMissing, int, int> {};
}  // namespace test_framework

bool operator==(const DuplicateAndMissing& lhs,
                const DuplicateAndMissing& rhs) {
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
      &FindDuplicateMissing, DefaultComparator{}, param_names);
}
