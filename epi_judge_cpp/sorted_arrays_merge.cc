#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;

struct Item {
  int val, row;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  auto comp = [](Item a, Item b) { return a.val > b.val; };
  std::priority_queue<Item, vector<Item>, decltype(comp)> pq(comp);

  std::unordered_map<int, int> map;
  //std::priority_queue<int, vector<int>, std::greater<int> > pq;

  int row_min = 0, size = 0;
  vector<int> ans;

  for (int i = 0; i < sorted_arrays.size(); ++i) {
    map[i] = 1;
    size += sorted_arrays[i].size();
    pq.push(Item{sorted_arrays[i][0], i});
  }

  while (row_min < sorted_arrays.size() && map[row_min] >= sorted_arrays[row_min].size())
    row_min++;

  while (!pq.empty()) {
    int row = pq.top().row;
    ans.emplace_back(pq.top().val);
    pq.pop();

    if (map[row] >= sorted_arrays[row].size())
      row = row_min;

    if (row_min != sorted_arrays.size()) {
      pq.push(Item{sorted_arrays[row][map[row]], row});
      map[row]++;
    }

    while (row_min < sorted_arrays.size() && map[row_min] >= sorted_arrays[row_min].size())
      row_min++;
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
