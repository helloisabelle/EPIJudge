#include <stdexcept>
#include <vector>
#include <bitset>


#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::invalid_argument;
using std::vector;

int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
  const int capacity = 1 << 16;
  int upper_bucket = 0;
  std::vector<size_t> candidates_upper(capacity, 0);
  std::bitset<capacity> candidates_lower;

  auto copy = stream_begin;
  while (copy != stream_end) {
    int upper = *copy >> 16;
    candidates_upper[upper]++;
    copy++;
  }

  for (int i = 0; i < capacity; i++) {
    if (candidates_upper[i] < capacity) {
      upper_bucket = i;
      break;
    }
  }

  copy = stream_begin;
  while (copy != stream_end) {
    if (*copy >> 16 == upper_bucket) {
      int lower = *copy << 16;
      lower = lower >> 16;
      candidates_lower.set(lower);
    }
    copy++;
  }

  for (int i = 0; i < capacity; i++) {
    if (candidates_lower[i] == 0) return (i | upper_bucket);
  }
  return 0;
}
void FindMissingElementWrapper(const vector<int>& stream) {
  try {
    int res = FindMissingElement(cbegin(stream), cend(stream));
    if (std::find(stream.begin(), stream.end(), res) != stream.end()) {
      throw TestFailure(std::to_string(res) + " appears in stream");
    }
  } catch (invalid_argument&) {
    throw TestFailure("Unexpected no missing element exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "absent_value_array.cc",
                         "absent_value_array.tsv", &FindMissingElementWrapper,
                         DefaultComparator{}, param_names);
}
