#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
  int count = 0;
  string ans = *stream_begin;
  while (stream_begin != stream_end) {
    if (*stream_begin == ans) ++count;
    else --count;
    ++stream_begin;
    // if element a = b, set to next item.

    aaaabbbbc                                                                                                                                           b

    if (!count) ans = *stream_begin;
  }
  return ans;
}
string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
