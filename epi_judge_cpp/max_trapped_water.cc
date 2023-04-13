#include <vector>
#include <cmath>

#include "test_framework/generic_test.h"
using std::vector;

int GetMaxTrappedWater(const vector<int>& heights) {
  int l = 0, r = size(heights) - 1;

  int ans = (r - l) * std::min(heights[r], heights[l]);

  while (l < r) {
    int curr = std::max(heights[l], heights[r]);
    if (curr == heights[l]) --r;
    else ++l;
    int n = (r - l) * std::min(heights[r], heights[l]);
    ans = std::max(ans, n);
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
                         &GetMaxTrappedWater, DefaultComparator{}, param_names);
}
