#include <stdexcept>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

void explore(vector<vector<char>>* board_ptr, int i, int j) {
  vector<vector<char>>&board = *board_ptr;
  std::queue<std::pair<int, int>> q;
  q.emplace(i, j);
  char save = board[i][j];
  while (!empty(q)) {
    const auto [x, y] = q.front();
    q.pop();
    if ((x < 0 || x >= board.size() || y < 0 || y >= board[0].size()) || board[x][y] != save) continue;
    board[x][y] = 'X';

//    for (const auto& [next_x, next_y] : vector<std::pair<int, int>>{
//             {x, y + 1}, {x, y - 1}, {x + 1, y}, {x - 1, y}}) {
//      if (next_x >= 0 && next_x < size(board) && next_y >= 0 &&
//          next_y < size(board[next_x]) && board[next_x][next_y] == save) {
//        q.emplace(next_x, next_y);
//      }
//    }

    q.emplace(x + 1, y);
    q.emplace(x - 1, y);
    q.emplace(x, y + 1);
    q.emplace(x, y - 1);
  }
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
  vector<vector<char>>&board = *board_ptr;

  for (int i = 0; i < size(board); i++) {
    int j = 0;
    if (board[i][j] == 'W') {
      explore(board_ptr, i, j);
    }
    j = size(board[0]) - 1;
    if (board[i][j] == 'W') {
      explore(board_ptr, i, j);
    }
  }

  for (int j = 0; j < size(board[0]); j++) {
    int i = 0;
    if (board[i][j] == 'W') {
      explore(board_ptr, i, j);
    }
    i = size(board) - 1;
    if (board[i][j] == 'W') {
      explore(board_ptr, i, j);
    }
  }

  for (int i = 0; i < size(board); i++) {
    for (int j = 0; j < size(board[0]); j++) {
      board[i][j] = board[i][j] != 'X' ? 'B' : 'W';
    }
  }

  return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
