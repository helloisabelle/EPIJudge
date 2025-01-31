#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {

  std::priority_queue<int, vector<int>, std::greater<int> > pq;

  vector<int> ans;
  auto it = sequence_begin;
  for (int i = 0; i < k && it != sequence_end; ++i, ++it) {
    pq.push(*it);
  }

  while (it != sequence_end) {
    pq.push(*it++);
    ans.emplace_back(pq.top());
    pq.pop();
    //pq.push(*it++);
  }

  while (!empty(pq)) {
    ans.emplace_back(pq.top());
    pq.pop();
  }

  return ans;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
