#include <string>
#include <algorithm>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
  string& a = *s;

  std::reverse(a.begin(), a.end());

  int i = 0;

  while (i < a.size()) {
    int j = i;
    while (j < a.size() && a[j] != ' ') j++;
    std::reverse(a.begin() + i, a.begin() + j);
    if (a[j] == ' ') j++;
    i = j;
  }

//  string w, ans;
//
//  for (int i = a.size() - 1; i >= 0; --i) {
//    if (a[i] != ' ') w += a[i];
//    else {
//      std::reverse(w.begin(), w.end());
//      ans.append(w + " ");
//      w = "";
//    }
//  }
//
//  std::reverse(w.begin(), w.end());
//  ans.append(w);
//
//  for (int i = 0; i < a.size(); ++i) {
//    a[i] = ans[i];
//  }
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
