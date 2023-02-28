#include <vector>
#include <algorithm>
#include<iostream>
#include <cmath>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};

struct Endpoint {
  int point, is_start;
};

int FindMaxSimultaneousEvents(const vector<Event>& A) {
  vector<Endpoint> e;
  int ans = 0, curr = 0;

  for (auto a : A) {
    e.emplace_back(Endpoint{a.start, 1});
    e.emplace_back(Endpoint{a.finish, 0});
  }

  std::sort(e.begin(), e.end(), [](const Endpoint& a, const Endpoint& b){
    return a.point == b.point ? a.is_start == 1 && b.is_start == 0 : a.point < b.point;
  });

  for (auto end : e) {
    if (end.is_start) ans = std::max(ans, ++curr);
    // like completing parentheses, if there is a closing one, that interval is no longer included...
    else --curr;
  }

  return ans;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
