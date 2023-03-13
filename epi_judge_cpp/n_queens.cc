#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>

#include "test_framework/generic_test.h"
using std::vector;

bool IsValid(const vector<int>& col) {
  int new_queen_idx = size(col) - 1;
  for (int i = 0; i < new_queen_idx; ++i) {
    // difference between queen here and most recently placed queen
    //diff between cols == diff between rows
    int diff = std::abs(col[i] - col[new_queen_idx]);
    // on same column or on diagonal
    if (diff == 0 || diff == new_queen_idx - i) return false;
  }
  return true;
}

void helper(int n, int row, vector<int>& col, vector<vector<int>>& res) {
  if (n == row) {
    // we have placed a queen on every row
    res.emplace_back(col);
  } else {
    for (int i = 0; i < n; i++) {
      col.emplace_back(i);
      // trying placing a queen here
      if (IsValid(col)) {
        helper(n, row + 1, col, res);
      }
      col.pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  vector<vector<int>> ans;
  std::vector<int> col;
  helper(n, 0, col, ans);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
