#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  std::unordered_map<char, int> letter_map;

  for (auto x : letter_text) ++letter_map[x];

  for (auto x : magazine_text) {
    if (letter_map.find(x) != letter_map.end()) {
     letter_map[x]--;
     if (letter_map[x] == 0) letter_map.erase(x);
     if (empty(letter_map)) break;
    }
  }

  return empty(letter_map);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
