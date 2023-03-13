#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void helper(string s, int num_pairs, int open, vector<string>& ans, int closed) {
  if (closed == num_pairs) {
    ans.emplace_back(s);
  } else {
    if (open + closed < num_pairs) {
      helper(s + "(", num_pairs, open + 1, ans, closed);
    }
    if (open > 0) {
      helper(s + ")", num_pairs, open - 1, ans, closed + 1);
    }
  }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  vector<string> ans;
  helper("", num_pairs, 0, ans, 0);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
