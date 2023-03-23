#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacityHelper(int i, int j, const vector<Item>& items, int capacity, std::vector<std::vector<int>>& cache) {
  if (i < 0) return 0;
  if (cache[i][j] == -1) {
    int without = OptimumSubjectToCapacityHelper(i - 1, j, items, capacity, cache);
    int with = j < items[i].weight ? 0 : items[i].value + OptimumSubjectToCapacityHelper(i - 1, j - items[i].weight, items, capacity, cache);
    cache[i][j] = std::max(without, with);
  }
  return cache[i][j];
}

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  int ans = 0;
  std::vector<std::vector<int>> cache(size(items), std::vector<int>(capacity + 1, 0));

  std::vector<int> prev(capacity + 1, 0), curr(capacity + 1, 0);

  //return OptimumSubjectToCapacityHelper(size(items) - 1, capacity, items, capacity, cache);

  for (int i = 0; i < size(items); ++i) {
    for (int j = 0; j <= capacity; ++j) {
      if (j >= items[i].weight) {
        if (i == 0) curr[j] = items[i].value;
        else curr[j] = std::max(prev[j], items[i].value + prev[j - items[i].weight]);
      } else if (i != 0) {
        curr[j] = prev[j];
      }
    }
    std::fill(prev.begin(), prev.end(), 0);
    std::swap(prev, curr);
  }

  return prev[capacity];

//  for (int i = 0; i < size(items); ++i) {
//    for (int j = 0; j <= capacity; ++j) {
//      if (j >= items[i].weight) {
//        if (i == 0) cache[i][j] = items[i].value;
//        else cache[i][j] = std::max(cache[i - 1][j], items[i].value + cache[i - 1][j - items[i].weight]);
//      } else if (i != 0) {
//        cache[i][j] = cache[i - 1][j];
//      }
//    }
//  }
//  return cache[size(items) - 1][capacity];
}

namespace test_framework {
template <>
struct SerializationTrait<Item> : UserSerTrait<Item, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
