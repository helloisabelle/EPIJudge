#include <vector>
#include <set>
#include <cmath>

#include "test_framework/generic_test.h"
using std::vector;

struct Obj {
  int a, b;
  double val;
  Obj(int a, int b) : a(a), b(b), val(a + b * sqrt(2)) {}

  bool operator <(Obj const & b) const {
      return (val < b.val);
  }
};
vector<double> GenerateFirstKABSqrt2(int k) {
  vector<double> ans(k, 0);
  vector<Obj> obs;
  int a = 0, b = 0;

  obs.emplace_back(Obj(0, 0));

  for (int i = 1; i < k; i++) {
    auto c = Obj(obs[a].a + 1, obs[a].b);
    auto d = Obj(obs[b].a, obs[b].b + 1);
    if (c.val <= d.val) {
      obs.emplace_back(c);
      ans[i] = c.val;
      ++a;
      if (c.val == d.val) ++b;
    } else {
      ans[i] = d.val;
      ++b;
      obs.emplace_back(d);
    }
  }

//  vector<double> ans;
//  std::set<Obj> s;
//  int a = 0, b = 0;
//  s.emplace(Obj{a, b, a + (b * sqrt(2))});
//
//  while (size(ans) != k) {
//    auto o = s.begin();
//    ans.emplace_back(o->val);
//    s.emplace(Obj{o->a + 1, o->b, (o->a + 1) + (o->b * sqrt(2))});
//    s.emplace(Obj{o->a, o->b + 1, o->a + ((o->b + 1) * sqrt(2))});
//    s.erase(o);
//  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
