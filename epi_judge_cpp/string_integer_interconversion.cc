#include <string>
#include <iostream>
#include <cmath>
#include <climits>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string ans;
  int min = 0;
  if (x < 0) {
    ans = "-";
    if (x == INT_MIN) {
        min = 1;
        x++;
    }
    x *= -1;

  }
  else ans = "+";
  if (x == 0) return "0";

  int len = trunc(log10(x)) + 1;

  while (len) {
    int top = x/pow(10, len - 1);
    ans.push_back(top + '0');
    x -= top * pow(10, len - 1);
    len--;
  }

  if (min) {
    ans[ans.size() - 1] = '8';
  }
  return ans;
}
int StringToInt(const string& s) {
  // TODO - you fill in here.
  int place = 1;
  int ans = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '-') ans *= -1;
    else if (s[i] == '+') break;
    else {
        ans += (s[i] - '0') * place;
        place *= 10;
    }
  }

  return ans;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
