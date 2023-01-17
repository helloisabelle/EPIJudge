#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::string;

string convert(int val, int b2) {
    if (val == 0) return "";
    int x = val % b2;
    char res = '0' + x;
    if (x >= 10) res = 'A' - 10 + x;

    return res + convert(val / b2, b2);
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  int p = 0, val = 0, neg = 0;
  if (num_as_string[0] == '-') neg = 1;


  val = accumulate(num_as_string.rbegin(), num_as_string.rend() - neg, 0, [&p, &b1](int sum, char c){
    return sum + ((isdigit(c) ? c - '0' : c - 'A' + 10) * pow(b1, p++));
  });

  string ans;
  ans = convert(val, b2);
//  while (val) {
//    int x = val % (int)pow(b2, 1);
//    ans.push_back(digits[x]);
//    val /= b2;
//  }

  if (neg) ans.push_back('-');
  if (ans.empty()) ans = '0';
  return {rbegin(ans), rend(ans)};
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
