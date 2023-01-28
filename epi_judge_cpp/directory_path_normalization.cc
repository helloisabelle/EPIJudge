#include <string>
#include <stack>
#include <iostream>
#include <sstream>

#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string& path) {
  std::stack<string> s;
  string copy = path;
  string delim = "/";
  char del = '/';

  std::stringstream ss(path);

  string t;
  while (getline(ss, t, del)) {
    if (t.size()) {
      if (t == "..") {
        if (s.empty() || s.top() == "..") s.emplace(t);
        else s.pop();
      } else if (t != ".") s.emplace(t);
    }
  }

//  while (copy.size()) {
//    string token = copy;
//    if (copy.find(delim) != -1) token = copy.substr(0, copy.find(delim));
//    if (token.size()) {
//      if (token == "..") {
//        if (s.empty() || s.top() == "..") s.push(token);
//        else s.pop();
//      } else if (token != ".") s.push(token);
//    }
//    if ((copy.find(delim) == -1) || (copy.find(delim) + 1 == copy.size() - 1 )) break;
//    copy = copy.substr(copy.find(delim) + 1, copy.size());
//  }
  string ans = "";

  while (!s.empty()) {
    ans += {s.top().rbegin(), s.top().rend()};
    s.pop();
    if (!s.empty()) ans += "/";
  }

  if (path.size() && path[0] == '/') ans += '/';

  return {ans.rbegin(), ans.rend()};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
