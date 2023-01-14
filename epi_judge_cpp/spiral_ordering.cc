#include <vector>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  // TODO - you fill in here.
  vector<int> ans;
  if (square_matrix.size() == 0) return {};
  int size = square_matrix.size() * square_matrix[0].size();

  int col_max = square_matrix[0].size() - 1;
  int row_max = square_matrix.size() - 1;
  int col_start = 0, row_start = 0;
  while (ans.size() < size) {
    for (int j = col_start; j < col_max || (size - ans.size() == 1); j++) {
      ans.push_back(square_matrix[row_start][j]);
    }

    for (int i = row_start; i < row_max; i++) {
      ans.push_back(square_matrix[i][col_max]);
    }

    for (int j = col_max; j > col_start; j--) {
      ans.push_back(square_matrix[row_max][j]);
    }

    for (int i = row_max; i > row_start; i--) {
      ans.push_back(square_matrix[i][col_start]);
    }

    col_max--, row_max--, row_start++, col_start++;
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
