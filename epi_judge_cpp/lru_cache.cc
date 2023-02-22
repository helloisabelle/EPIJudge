#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <list>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
 private:
  std::unordered_map<int, std::pair<std::list<int>::iterator, int> > map;
  std::list<int> l;
  size_t lru_capacity;
  size_t size;
 public:
  LruCache(size_t capacity) {
    lru_capacity = capacity;
    size = 0;
  }
  int Lookup(int isbn) {
    auto it = map.find(isbn);
    if (it == map.end()) return -1;
    else {
      l.erase(it->second.first);
      l.emplace_back(isbn);
      auto l_it = l.end();
      --l_it;
      it->second.first = l_it;
      return map.find(isbn)->second.second;
    }
  }
  void Insert(int isbn, int price) {
    if (size == lru_capacity && map.find(isbn) == map.end()) {
      Erase(l.front());
    }
    auto it = map.find(isbn);
    if (it == map.end()) {
      l.emplace_back(isbn);
      auto l_it = l.end();
      --l_it;
      map[isbn] = std::make_pair(l_it, price);
      ++size;
    }
    else {
      l.erase(it->second.first);
      l.emplace_back(isbn);
      auto l_it = l.end();
      --l_it;
      it->second.first = l_it;
    }
    return;
  }
  bool Erase(int isbn) {
    auto it = map.find(isbn);
    if (it != map.end()) {
      l.erase(it->second.first);
      map.erase(isbn);
      --size;
      return true;
    } else return false;
  }
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
