#include <vector>
#include <iostream>
#include <cmath>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
  vector<Interval> copy(disjoint_intervals);
  std::sort(copy.begin(), copy.end(), [](const Interval& a, const Interval& b) {
    return a.left < b.left;
  });
  int begin = 0; int end = -1;
  int erase_start = -1, erase_end = -1;
  int index = -1;

  for (int i = 0; i < copy.size(); i++) {
    // if new_interval overlaps
    if (new_interval.right >= copy[i].left && new_interval.left <= copy[i].right) {
    //if (!(new_interval.right < copy[i].left) && !(new_interval.left > copy[i].right)) {
      if (erase_start == -1) {
        erase_start = i;
        begin = std::min(new_interval.left, copy[i].left);
      }
      erase_end = i;
      end = std::max(new_interval.right, copy[i].right);
    } else if (new_interval.right < copy[i].left && index == -1) index = i;
  }

  if (erase_start + erase_end >= 0) {
    copy.erase(copy.begin() + erase_start, copy.begin() + erase_end + 1);
    copy.insert(copy.begin() + erase_start, Interval{begin, end});
  } else if (index == -1) copy.emplace_back(new_interval);
  else copy.insert(copy.begin() + index, new_interval);

  return copy;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework
bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
