#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "test_framework/generic_test.h"
using std::vector;

//int NumCombinationsForFinalScoreHelper(int final_score,
//                                 const vector<int>& individual_play_scores, vector<int>& cache) {
//  if (final_score < 0) return 0;
//  else if (final_score == 0) cache[final_score] = 1;
//  else if (cache[final_score] != -1) return cache[final_score];
//  else {
//    cache[final_score] = 0;
//    for (int i = 0; i < size(individual_play_scores); ++i) {
//      cache[final_score] += NumCombinationsForFinalScoreHelper(final_score - individual_play_scores[i], individual_play_scores, cache);
//    }
//  }
//
//  return cache[final_score];
//}
//
//int NumCombinationsForFinalScore(int final_score,
//                                 const vector<int>& individual_play_scores) {
//  vector<int> cache(final_score + 1, 0);
//  for (int i = 0; i <= final_score; i++) {
//    for (int j = 0; j < individual_play_scores.size(); j++) {
//      if (i - individual_play_scores[j] > 0)
//        cache[i] += cache[i - individual_play_scores[j]];
//      else if (i - individual_play_scores[j] == 0) ++cache[i];
//    }
//  }
//
//  return cache[final_score];
//
//
//  //return NumCombinationsForFinalScoreHelper(final_score, individual_play_scores, cache);
//}

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  vector<vector<int>> v(
      size(individual_play_scores), vector<int>(final_score + 1, 0));
  for (int i = 0; i < size(individual_play_scores); ++i) {
    v[i][0] = 1;  // One way to reach 0.
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

// score = 3

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
