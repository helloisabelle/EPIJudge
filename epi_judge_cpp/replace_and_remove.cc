#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  int ans = 0;
  int count = 0;
  int write_index = 0;
  for (int i = 0; i < size; i++) {
    if (s[i] != 'b') s[write_index++] = s[i];
    if (s[i] == 'a') count++;
  }

  int x = write_index + count - 1;
  ans = x + 1;
  write_index--;
  while (write_index >= 0) {
    if (s[write_index] == 'a') {
      s[x--] = 'd';
      s[x--] = 'd';
    } else s[x--] = s[write_index];
    write_index--;
  }

//
//  while (i < size) {
//    if (s[i] == 'b') {
//      for (int j = i; j < size - 1; ++j) {
//          s[j] = s[j + 1];
//      }
//      size--;
//    } else i++;
//  }
//
//  int x = 0;
//  while (x < size) {
//    if (s[x] == 'a') {
//      s[x] = 'd';
//      char save = s[x + 1];
//      s[x + 1] = 'd';
//      for (int j = x + 2; j < size + 1; ++j) {
//           char prev = s[j];
//           s[j] = save;
//           save = prev;
//      }
//      size++;
//    } else x++;
//  }

  return ans;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
