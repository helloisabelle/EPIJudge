#include <string>
#include <vector>
#include <cmath>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

//int LevenshteinDistanceHelper(int a, int b, const string& A, const string& B, vector<vector<int>>* cache_ptr) {
//  vector<vector<int>>& cache = *cache_ptr;
//  if (a < 0) return b + 1;
//  else if (b < 0) return a + 1;
//
//  if (cache[a][b] == -1) {
//    int m = LevenshteinDistanceHelper(a - 1, b - 1, A, B, cache_ptr);
//    if (A[a] != B[b]) {
//      m = std::min(m, LevenshteinDistanceHelper(a - 1, b, A, B, cache_ptr));
//      m = std::min(m, LevenshteinDistanceHelper(a , b - 1, A, B, cache_ptr));
//      ++m;
//    }
//    cache[a][b] = m;
//  }
//  return cache[a][b];
//}
//
//int LevenshteinDistance(const string& A, const string& B) {
//  return LevenshteinDistanceHelper(size(A) - 1, size(B) - 1, A, B, std::make_unique<vector<vector<int>>>(vector<vector<int>>(size(A), vector<int>(size(B), -1))).get());
//}

int LevenshteinDistance(const string& A, const string& B) {
  std::vector<int> prev(size(B) + 1, 0), curr(size(B) + 1, 0);
  for (int i = 0; i <= size(A); ++i) {
    for (int j = 0; j <= size(B); ++j) {
      if (i == 0) curr[j] = j;
      else if (j == 0) curr[j] = i;
      else {
        curr[j] = prev[j - 1];
        if (A[i - 1] != B[j - 1]) {
          curr[j] = 1 + std::min({curr[j], curr[j - 1], prev[j]});
        }
      }
    }
    std::fill(prev.begin(), prev.end(), 0);
    std::swap(prev, curr);
  }

  return prev.back();
//  vector<vector<int>> cache(size(A) + 1, vector<int>(size(B) + 1, 0));
//  for (int i = 0; i <= size(A); ++i) {
//    for (int j = 0; j <= size(B); ++j) {
//      if (i == 0) cache[i][j] = j;
//      else if (j == 0) cache[i][j] = i;
//      else {
//        cache[i][j] = cache[i - 1][j - 1];
//        if (A[i - 1] != B[j - 1]) {
//          cache[i][j] = 1 + std::min({cache[i][j], cache[i][j - 1], cache[i - 1][j]});
//        }
//      }
//    }
//  }
//
//  return cache[size(A)][size(B)];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
