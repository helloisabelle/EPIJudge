#include <algorithm>
#include "test_framework/generic_test.h"



//void NumberOfWaysHelper(int i, int j, std::vector<std::vector<int>>& cache, int n, int m) {
//  if (i < 0 || j < 0 || cache[i][j] != 0) return;
//  if (i + 1 < n) cache[i][j] += cache[i + 1][j];
//  if (j + 1 < m) cache[i][j] += cache[i][j + 1];
//}

//i - 1 will be curr
//
//needs to know i = curr
//
//curr i needs to know i + 1 = prev
//
//i - 1 i

void NumberOfWaysHelper(int j, std::vector<int>& prev, std::vector<int>& curr, int m) {
  if (j < 0 || curr[j] != 0) return;
  curr[j] += prev[j];
  if (j + 1 < m) curr[j] += curr[j + 1];
}

int NumberOfWays(int n, int m) {
  std::vector<int> prev(m, 0), curr(m, 0);
  prev[m - 1] = 1;

  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      NumberOfWaysHelper(j, prev, curr, m);
      NumberOfWaysHelper(j - 1, prev, curr, m);
    }
    std::fill(prev.begin(), prev.end(), 0);
    std::swap(prev, curr);
  }

  return prev[0];

//  std::vector<std::vector<int>> cache(n, std::vector<int>(m, 0));
//  cache[n - 1][m - 1] = 1;

//  for (int i = n - 1; i >= 0; --i) {
//    for (int j = m - 1; j >= 0; --j) {
//      NumberOfWaysHelper(i - 1, j, cache, n, m);
//      NumberOfWaysHelper(i, j - 1, cache, n, m);
//    }
//  }
//
//  return cache[0][0];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
