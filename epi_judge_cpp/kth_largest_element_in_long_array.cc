#include <vector>
#include <queue>
#include <iostream>
#include "test_framework/generic_test.h"
using std::vector;

int FindKthLargestUnknownLength(vector<int>::const_iterator stream_begin,
                                const vector<int>::const_iterator& stream_end,
                                int k) {
  std::priority_queue<int, vector<int>, std::greater<int> > pq;

  auto it = stream_begin;
  while (it != stream_end) {
    pq.push(*it);
    if (pq.size() == k + 1) pq.pop();
    it++;
  }

  return pq.top();
}
int FindKthLargestUnknownLengthWrapper(const vector<int>& stream, int k) {
  return FindKthLargestUnknownLength(stream.cbegin(), stream.cend(), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream", "k"};
  return GenericTestMain(args, "kth_largest_element_in_long_array.cc",
                         "kth_largest_element_in_long_array.tsv",
                         &FindKthLargestUnknownLengthWrapper,
                         DefaultComparator{}, param_names);
}
