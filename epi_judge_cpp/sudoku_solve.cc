#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::begin;
using std::end;
using std::vector;

struct Cell {
  int row, col;
};

bool isValid(vector<vector<int>>& partial_assignment, int r, int c, int val) {
  for (int i = 0; i < partial_assignment.size(); i++) {
    if (partial_assignment[i][c] == val) return false;
  }

  for (int i = 0; i < partial_assignment[0].size(); i++) {
    if (partial_assignment[r][i] == val) return false;
  }

  int row_start = r / 3;
  int col_start = c / 3;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (partial_assignment[(row_start * 3) + i][(col_start * 3) + j] == val) return false;
    }
  }

  return true;
}

void SolveSudokuHelper(vector<vector<int>>& v, std::queue<Cell> q, int& ans) {
  if (q.size() == 0) {
    ans = 1;
  } else if (ans == 0) {
    Cell curr = q.front();
    q.pop();
    for (int k = 1; k <= 9; k++) {
      if (isValid(v, curr.row, curr.col, k)) {
        v[curr.row][curr.col] = k;
        SolveSudokuHelper(v, q, ans);
        if (ans == 1) break;
      }
      v[curr.row][curr.col] = 0;
    }
  }
}

bool SolveSudoku(vector<vector<int>>* partial_assignment) {
  vector<vector<int>>& v = *partial_assignment;
  std::queue<Cell> q;

  int count = 0;
  for (int i = 0; i < size(v); i++) {
    for (int j = 0; j < size(v[0]); j++) {
      if (v[i][j] == 0) {
        q.emplace(Cell{i, j});
      }
    }
  }
  int ans = 0;

  SolveSudokuHelper(*partial_assignment, q, ans);
  return ans;
}
vector<int> GatherColumn(const vector<vector<int>>& data, size_t i) {
  vector<int> result;
  for (auto& row : data) {
    result.push_back(row[i]);
  }
  return result;
}

vector<int> GatherSquareBlock(const vector<vector<int>>& data,
                              size_t block_size, size_t n) {
  vector<int> result;
  size_t block_x = n % block_size;
  size_t block_y = n / block_size;
  for (size_t i = block_x * block_size; i < (block_x + 1) * block_size; i++) {
    for (size_t j = block_y * block_size; j < (block_y + 1) * block_size; j++) {
      result.push_back(data[i][j]);
    }
  }

  return result;
}

void AssertUniqueSeq(const vector<int>& seq) {
  vector<bool> seen(seq.size(), false);
  for (auto& x : seq) {
    if (x == 0) {
      throw TestFailure("Cell left uninitialized");
    }
    if (x < 0 || x > seq.size()) {
      throw TestFailure("Cell value out of range");
    }
    if (seen[x - 1]) {
      throw TestFailure("Duplicate value in section");
    }
    seen[x - 1] = true;
  }
}

void SolveSudokuWrapper(TimedExecutor& executor,
                        const vector<vector<int>>& partial_assignment) {
  vector<vector<int>> solved = partial_assignment;

  executor.Run([&] { SolveSudoku(&solved); });

  if (!std::equal(begin(partial_assignment), end(partial_assignment),
                  begin(solved), end(solved), [](auto br, auto cr) {
                    return std::equal(begin(br), end(br), begin(cr), end(cr),
                                      [](int bcell, int ccell) {
                                        return bcell == 0 || bcell == ccell;
                                      });
                  }))
    throw TestFailure("Initial cell assignment has been changed");

  auto block_size = static_cast<size_t>(sqrt(solved.size()));

  for (size_t i = 0; i < solved.size(); i++) {
    AssertUniqueSeq(solved[i]);
    AssertUniqueSeq(GatherColumn(solved, i));
    AssertUniqueSeq(GatherSquareBlock(solved, block_size, i));
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "partial_assignment"};
  return GenericTestMain(args, "sudoku_solve.cc", "sudoku_solve.tsv",
                         &SolveSudokuWrapper, DefaultComparator{}, param_names);
}
