#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

bool DecomposeIntoDictionaryWordsHelper(
    const string& domain, const unordered_set<string>& dictionary, vector<string>& ans, std::unordered_map<string, int>& cache) {
  if (cache[domain] == 2) return false;
  if (cache[domain] || dictionary.count(domain)) {
    ans.emplace_back(domain);
    cache[domain] = 1;
    return true;
  }

  for (int i = 1; i < size(domain); ++i) {
    auto pre = domain.substr(0, i);
    if (cache[pre] == 1 || dictionary.count(pre)) {
      ans.emplace_back(pre);
      cache[pre] = 1;
      auto post = domain.substr(i, size(domain) - i);
      if (DecomposeIntoDictionaryWordsHelper(post, dictionary, ans, cache)) {
        cache[domain] = 1;
        return true;
      }
      ans.pop_back();
    }
  }

  cache[domain] = 2;
  return false;
}

vector<string> DecomposeIntoDictionaryWords(
    const string& domain, const unordered_set<string>& dictionary) {
  std::unordered_map<string, int> cache;
  vector<string> ans;
  // DecomposeIntoDictionaryWordsHelper(domain, dictionary, ans, cache);

  vector<int> last_length(size(domain), -1);

  for (int i = 0; i < size(domain); ++i) {
    if (dictionary.count(domain.substr(0, i + 1))) last_length[i] = i + 1;
    else {
      for (int j = 0 ; j < i; j++) {
        if (last_length[j] != -1 && dictionary.count(domain.substr(j + 1, i - j))) {
          last_length[i] = i - j;
          break;
        }
      }
    }
  }

  if (last_length.back() != -1) {
    int i = size(domain) - 1;
    while (i >= 0) {
      ans.emplace_back(domain.substr(i - last_length[i] + 1, last_length[i]));
      i -= last_length[i];
    }
  }


  return {ans.rbegin(), ans.rend()};
}
void DecomposeIntoDictionaryWordsWrapper(
    TimedExecutor& executor, const string& domain,
    const unordered_set<string>& dictionary, bool decomposable) {
  vector<string> result = executor.Run(
      [&] { return DecomposeIntoDictionaryWords(domain, dictionary); });
  if (!decomposable) {
    if (!result.empty()) {
      throw TestFailure("domain is not decomposable");
    }
    return;
  }

  if (std::any_of(std::begin(result), std::end(result),
                  [&](const std::string& s) { return !dictionary.count(s); })) {
    throw TestFailure("Result uses words not in dictionary");
  }

  if (std::accumulate(std::begin(result), std::end(result), string()) !=
      domain) {
    throw TestFailure("Result is not composed into domain");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "domain", "dictionary",
                                       "decomposable"};
  return GenericTestMain(args, "is_string_decomposable_into_words.cc",
                         "is_string_decomposable_into_words.tsv",
                         &DecomposeIntoDictionaryWordsWrapper,
                         DefaultComparator{}, param_names);
}
