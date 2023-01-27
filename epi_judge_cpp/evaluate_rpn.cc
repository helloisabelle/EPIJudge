#include <string>
#include <stack>
#include <ctype.h>
#include <iostream>

#include "test_framework/generic_test.h"

int Evaluate(const std::string& expression) {
  std::stack<int> s;
  std::string copy = expression;
  std::string delimiter = ",";

  while (copy.size()) {
    std::string token = copy;
    if (copy.find(delimiter) != -1) token = copy.substr(0, copy.find(delimiter));
    if (token.size() == 1 && !isdigit(token[0])) {
      int b = s.top();
      s.pop();
      int a = s.top();
      s.pop();
      if (token == "/") s.emplace(a / b);
      else if (token == "*") s.emplace(a * b);
      else if (token == "-") s.emplace(a - b);
      else if (token == "+") s.emplace(a + b);
    } else s.emplace(std::stoi(token));
    if (copy.find(delimiter) != -1) {
      copy = copy.substr(copy.find(delimiter) + 1, copy.size());
    } else break;
  }
eval
  return s.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
