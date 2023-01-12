#include <vector>
#include <cmath>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> GeneratePrimes(int n) {
  vector<int> ans;
  vector<bool> val(n + 1, true);
  for (int i = 2; i <= n; i++) {
    int flag = 0;
    if (val[i] == false) continue;

    for (int j = 2; j <= sqrt(i) && j != i; j++) {
        if (i % j == 0){
            flag = 1;
            for (int k = i*2; k <= n; k += i) {
                val[k] = false;
            }
            break;
        }
    }
    if (!flag) ans.emplace_back(i);
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
