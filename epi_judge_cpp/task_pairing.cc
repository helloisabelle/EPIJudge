#include <tuple>
#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct PairedTasks {
  int task_1, task_2;
};

vector<PairedTasks> OptimumTaskAssignment(vector<int> task_durations) {
  std::sort(task_durations.begin(), task_durations.end());
  vector<PairedTasks> ans;
  int l = 0, r = size(task_durations) - 1;

  while (l < r) {
    ans.emplace_back(PairedTasks{task_durations[l++], task_durations[r--]});
  }
  return ans;
}

namespace test_framework {
template <>
struct SerializationTrait<PairedTasks> : UserSerTrait<PairedTasks, int, int> {};
}  // namespace test_framework

bool operator==(const PairedTasks& lhs, const PairedTasks& rhs) {
  return std::tie(lhs.task_1, lhs.task_2) == std::tie(rhs.task_1, rhs.task_2);
}

std::ostream& operator<<(std::ostream& out, const PairedTasks& t) {
  return PrintTo(out, std::make_tuple(t.task_1, t.task_2));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"task_durations"};
  return GenericTestMain(args, "task_pairing.cc", "task_pairing.tsv",
                         &OptimumTaskAssignment, DefaultComparator{},
                         param_names);
}
