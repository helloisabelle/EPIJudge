#include <vector>
#include <cmath>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double start = prices[0], ans = 0;
  for (int i = 1; i < prices.size(); i++) {
    double val = prices[i] - start;
    ans = std::max(val, ans);
    start = std::min(prices[i], start);
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
