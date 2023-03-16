#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  vector<vector<int>> v(size(individual_play_scores), vector<int>(final_score + 1, 0));
  for (int i = 0; i < size(individual_play_scores); ++i) {
    v[i][0] = 1;
    for (int j = 1; j <= final_score; ++j) {
      int without_this_play = i >= 1 ? v[i - 1][j] : 0;
      int with_this_play =
          j >= individual_play_scores[i]
              ? v[i][j - individual_play_scores[i]]
              : 0;
      v[i][j] = without_this_play + with_this_play;
    }
  }
  return v.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
