#include <string>
#include <stack>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  std::stack<char> stack;
  std::unordered_map<char, char> map = {
    {'(', ')'}, {'{', '}'}, {'[', ']'}
  };

  for (int i = 0; i < s.size(); i++) {
    if (map.find(s[i]) != map.end()) stack.emplace(s[i]);
    else {
      if (stack.empty()) return false;
      if (map[stack.top()] != s[i]) return false;
      else stack.pop();
    }
  }

  return stack.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
