#include <deque>
#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

struct Coord {
  int x, y;
};

void FlipColorHelper(Coord c, vector<deque<bool>>* image_ptr, bool color) {
  vector<deque<bool>>& image = *image_ptr;
  if ((c.x < 0 || c.x >= image.size() || c.y < 0 || c.y >= image[0].size()) || image[c.x][c.y] == color) return;
  image[c.x][c.y] = color;

  FlipColorHelper(Coord{c.x + 1, c.y}, image_ptr, color);
  FlipColorHelper(Coord{c.x, c.y + 1}, image_ptr, color);
  FlipColorHelper(Coord{c.x - 1, c.y}, image_ptr, color);
  FlipColorHelper(Coord{c.x, c.y - 1}, image_ptr, color);

  return;
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  vector<deque<bool>>& image = *image_ptr;
  bool c = !image[x][y];
  // FlipColorHelper(Coord{x, y}, image_ptr, c);

  // BFS
  std::queue<Coord> q;
  q.emplace(Coord{x, y});

  while (!q.empty()) {
    Coord coord = q.front();
    q.pop();
    if ((coord.x < 0 || coord.x >= image.size() || coord.y < 0 || coord.y >= image[0].size()) || image[coord.x][coord.y] == c) continue;
    image[coord.x][coord.y] = c;
    q.emplace(Coord{coord.x + 1, coord.y});
    q.emplace(Coord{coord.x - 1, coord.y});
    q.emplace(Coord{coord.x, coord.y + 1});
    q.emplace(Coord{coord.x, coord.y - 1});
  }
  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
