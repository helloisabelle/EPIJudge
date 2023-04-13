#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <climits>
using std::vector;
const int kMPG = 20;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
int FindAmpleCity(const vector<int>& gallons, const vector<int>& distances) {
  vector<int> c_gallons(gallons), c_distances(distances);

//  vector<int> candidates;
//  for (int i = 0; i < size(c_gallons); i++) {
//    if (gallons[i] >= (distances[i]/20)) candidates.emplace_back(i);
//  }

  int ans = 0, curr_gas = 0, min_gas = INT_MAX;

  for (int i = 0; i < size(gallons); i++) {

    if (curr_gas < min_gas) {
      min_gas = curr_gas;
      ans = i;
    }
    curr_gas -= distances[i]/20;
    curr_gas += gallons[i];
//    if ()
//    if (gallons[i] >= (distances[i]/20)) candidates.emplace_back(i);
  }

//  for (int i = 0; i < size(candidates); i++) {
//    std::rotate(c_gallons.begin(), c_gallons.begin() + candidates[i], c_gallons.end());
//    std::rotate(c_distances.begin(), c_distances.begin() + candidates[i], c_distances.end());
//    int curr = 0, flag = 0;
//    for (int j = 0; j < size(c_gallons); j++) {
//      curr += c_gallons[j];
//      curr -= (c_distances[j]/20);
//      if (curr < 0) {
//        flag++;
//        break;
//      }
//    }
//    if (flag == 0) {
//      return candidates[i];
//    }
//    std::rotate(c_gallons.begin(), c_gallons.begin() + c_gallons.size() - candidates[i], c_gallons.end());
//    std::rotate(c_distances.begin(), c_distances.begin() + c_distances.size() - candidates[i], c_distances.end());
//  }

  return ans;
}
void FindAmpleCityWrapper(TimedExecutor& executor, const vector<int>& gallons,
                          const vector<int>& distances) {
  int result = executor.Run([&] { return FindAmpleCity(gallons, distances); });
  const int num_cities = gallons.size();
  int tank = 0;
  for (int i = 0; i < num_cities; ++i) {
    int city = (result + i) % num_cities;
    tank += gallons[city] * kMPG - distances[city];
    if (tank < 0) {
      throw TestFailure(FmtStr("Out of gas on city {}", i));
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "gallons", "distances"};
  return GenericTestMain(args, "refueling_schedule.cc",
                         "refueling_schedule.tsv", &FindAmpleCityWrapper,
                         DefaultComparator{}, param_names);
}
