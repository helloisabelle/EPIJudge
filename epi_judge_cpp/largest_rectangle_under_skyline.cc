#include <vector>
#include <stack>

#include "test_framework/generic_test.h"
using std::vector;

bool newPillarOrEnd(const vector<int>& heights, int i, int prev_pillar) {
  return i < size(heights) ? heights[i] <= heights[prev_pillar] : true;
}

int CalculateLargestRectangle(const vector<int>& heights) {
  int ans = 0;
  std::stack<int> s;

  for (int i = 0; i <= size(heights); ++i) {
    while (!empty(s) && newPillarOrEnd(heights, i, s.top())) {
      int height = heights[s.top()];
      s.pop();

      // largest rect that s.top() supports ends at i
      int width = empty(s) ? i : i - s.top() - 1;
      ans = std::max(ans, width * height);
    }
    s.emplace(i);
  }

  return ans;

//  for (int i = 0; i < size(heights); ++i) {
//    int val = heights[i];
//    for (int j = i - 1; j >= 0; --j) {
//      if (heights[j] >= heights[i]) val += heights[i];
//      else break;
//    }
//    for (int k = i + 1; k < size(heights); ++k) {
//      if (heights[k] >= heights[i]) val += heights[i];
//      else break;
//    }
//    ans = std::max(ans, val);
//  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
                         "largest_rectangle_under_skyline.tsv",
                         &CalculateLargestRectangle, DefaultComparator{},
                         param_names);
}
