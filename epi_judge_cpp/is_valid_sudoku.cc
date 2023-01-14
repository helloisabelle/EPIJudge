#include <vector>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  vector<int> num(10);

  for (int i = 0; i < partial_assignment.size(); i++) {
    std::iota(num.begin(), num.end(), 0);
    for (int j = 0; j < partial_assignment[0].size(); j++) {
        if (num[partial_assignment[i][j]] == -1) return false;
        if (partial_assignment[i][j] != 0) num[partial_assignment[i][j]] = -1;
    }
  }

  for (int i = 0; i < partial_assignment[0].size(); i++) {
      std::iota(num.begin(), num.end(), 0);
      for (int j = 0; j < partial_assignment.size(); j++) {
          if (num[partial_assignment[j][i]] == -1) return false;
          if (partial_assignment[j][i] != 0) num[partial_assignment[j][i]] = -1;
      }
  }

  for (int i = 0; i < partial_assignment.size(); i+=3) {
      for (int j = 0; j < partial_assignment[0].size(); j+=3) {
          std::iota(num.begin(), num.end(), 0);
          for (int k = i; k < i + 3; k++) {
              for (int l = j; l < j + 3; l++) {
                  if (num[partial_assignment[k][l]] == -1) return false;
                  if (partial_assignment[k][l] != 0) num[partial_assignment[k][l]] = -1;
              }
          }
      }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
