#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // TODO - you fill in here.
  int neg = 1;
  vector<vector<int> > add;
  vector<int> ans;

  if (num1[0] < 0) {
    neg *= -1;
    num1[0] *= -1;
  }
  if (num2[0] < 0) {
    neg *= -1;
    num2[0] *= -1;
  }

  if (num2.size() < num1.size()) std::swap(num2, num1);
  int m = 0;
    for (int i = num1.size() - 1; i >= 0; i--){
        vector<int> v;
        int to_add = 0;
        for (int k = i; k < num1.size() - 1; k++){
            v.emplace_back(0);
        }
        for (int j = num2.size() - 1; j >= 0; j--){
          int val = num2[j] * num1[i] + to_add;
          if (val >= 10) {
            to_add = val/10;
            val = val % 10;
          }
          else to_add = 0;
          v.push_back(val);
        }
        if (to_add != 0) v.push_back(to_add);
        m = std::max(m, (int)v.size());
        add.push_back(v);
    }

  int carry = 0;
  for (int i = 0; i < m; i++){
    int val = carry;
    for (auto x : add) {
     if (x.size() > i) {
        val += x[i];
     }
    }
    if (val >= 10) {
        carry = val/10;
        val = val % 10;
    } else carry = 0;
    ans.push_back(val);
  }
  if (carry != 0) ans.push_back(carry);

  std::reverse(ans.begin(), ans.end());

  if (ans[0] == 0) return {0};
  ans[0] *= neg;
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
