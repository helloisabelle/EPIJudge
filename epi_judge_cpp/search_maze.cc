#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kWhite, kBlack };
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

struct hash_fn
{
   std::size_t operator() (const Coordinate &node) const
   {
       std::size_t h1 = std::hash<int>()(node.x);
       std::size_t h2 = std::hash<int>()(node.y);

       return h1 ^ h2;
   }
};

struct Obj {
  Coordinate c;
  vector<Coordinate> path;
};

vector<Coordinate> BFS(vector<vector<Color>> maze, const Coordinate& e, std::unordered_set<Coordinate, hash_fn>& visited, std::queue<Obj> q) {
  while (!q.empty()) {
    Obj o = q.front();
    Coordinate c = o.c;
    q.pop();
    if (c == e) return o.path;
    if (visited.count(c)) continue;
    visited.emplace(c);
    if (c.x + 1 < maze.size() && maze[c.x + 1][c.y] == Color::kWhite) {
      Coordinate d{c.x + 1, c.y};
      vector<Coordinate> n(o.path);
      n.emplace_back(d);
      q.emplace(Obj{d, n});
    }

    if (c.y + 1 < maze[0].size() && maze[c.x][c.y + 1] == Color::kWhite) {
      Coordinate d{c.x, c.y + 1};
      vector<Coordinate> n(o.path);
      n.emplace_back(d);
      q.emplace(Obj{d, n});
    }

    if (c.x - 1 >= 0 && maze[c.x - 1][c.y] == Color::kWhite) {
      Coordinate d{c.x - 1, c.y};
      vector<Coordinate> n(o.path);
      n.emplace_back(d);
      q.emplace(Obj{d, n});
    }

    if (c.y - 1 >= 0 && maze[c.x][c.y - 1] == Color::kWhite) {
      Coordinate d{c.x, c.y - 1};
      vector<Coordinate> n(o.path);
      n.emplace_back(d);
      q.emplace(Obj{d, n});
    }
  }

  return {};
}

bool DFS(vector<vector<Color>> maze, const Coordinate& c,
                              const Coordinate& e, vector<Coordinate>& path, std::unordered_set<Coordinate, hash_fn>& visited) {
  if (c == e) return true;
  if (visited.count(c)) return false;
  visited.emplace(c);
  if (c.x + 1 < maze.size() && maze[c.x + 1][c.y] == Color::kWhite) {
    Coordinate d{c.x + 1, c.y};
    path.emplace_back(d);
    if (DFS(maze, d, e, path, visited)) return true;
    path.pop_back();
  }

  if (c.y + 1 < maze[0].size() && maze[c.x][c.y + 1] == Color::kWhite) {
    Coordinate d{c.x, c.y + 1};
    path.emplace_back(d);
    if (DFS(maze, d, e, path, visited)) return true;
    path.pop_back();
  }

  if (c.x - 1 >= 0 && maze[c.x - 1][c.y] == Color::kWhite) {
    Coordinate d{c.x - 1, c.y};
    path.emplace_back(d);
    if (DFS(maze, d, e, path, visited)) return true;
    path.pop_back();
  }

  if (c.y - 1 >= 0 && maze[c.x][c.y - 1] == Color::kWhite) {
    Coordinate d{c.x, c.y - 1};
    path.emplace_back(d);
    if (DFS(maze, d, e, path, visited)) return true;
    path.pop_back();
  }
  return false;
}

bool DFS3(vector<vector<Color>>& maze, const Coordinate& c,
                              const Coordinate& e, vector<Coordinate>& path) {
  if ((c.x < 0 || c.x >= maze.size() || c.y < 0 || c.y >= maze[0].size()) || maze[c.x][c.y] == Color::kBlack) return false;
  path.emplace_back(c);
  maze[c.x][c.y] = Color::kBlack;
  if (c == e) return true;

  if (DFS3(maze, Coordinate{c.x + 1, c.y}, e, path)) return true;
  if (DFS3(maze, Coordinate{c.x - 1, c.y}, e, path)) return true;
  if (DFS3(maze, Coordinate{c.x, c.y + 1}, e, path)) return true;
  if (DFS3(maze, Coordinate{c.x, c.y - 1}, e, path)) return true;

  path.pop_back();
  return false;
}

bool DFS2(vector<vector<Color>>& maze, const Coordinate& c,
                              const Coordinate& e, vector<Coordinate>& path) {
  if (c == e) return true;

  if (c.x + 1 < maze.size() && maze[c.x + 1][c.y] == Color::kWhite) {
    Coordinate d{c.x + 1, c.y};
    path.emplace_back(d);
    maze[d.x][d.y] = Color::kBlack;
    if (DFS2(maze, d, e, path)) return true;
    path.pop_back();
  }

  if (c.y + 1 < maze[0].size() && maze[c.x][c.y + 1] == Color::kWhite) {
    Coordinate d{c.x, c.y + 1};
    path.emplace_back(d);
    maze[d.x][d.y] = Color::kBlack;
    if (DFS2(maze, d, e, path)) return true;
    path.pop_back();
  }

  if (c.x - 1 >= 0 && maze[c.x - 1][c.y] == Color::kWhite) {
    Coordinate d{c.x - 1, c.y};
    path.emplace_back(d);
    maze[d.x][d.y] = Color::kBlack;
    if (DFS2(maze, d, e, path)) return true;
    path.pop_back();
  }

  if (c.y - 1 >= 0 && maze[c.x][c.y - 1] == Color::kWhite) {
    Coordinate d{c.x, c.y - 1};
    path.emplace_back(d);
    maze[d.x][d.y] = Color::kBlack;
    if (DFS2(maze, d, e, path)) return true;
    path.pop_back();
  }

  return false;
}


vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
  vector<Coordinate> path = {s};
  std::unordered_set<Coordinate, hash_fn> visited;
  DFS2(maze, s, e, path);

  if (path.back().x != e.x || path.back().y != e.y) {
    return {};
  }
//  std::queue<Obj> q;
//  q.emplace(Obj{s, {s}});
//  return BFS(maze, e, visited, q);
  return path;
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
