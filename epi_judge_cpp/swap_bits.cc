#include "test_framework/generic_test.h"
long long SwapBits(long long x, int i, int j) {
  // TODO - you fill in here.

  if (((x >> i) & 1) != ((x >> j) & 1)) {
    // 1L = 1 long long
    unsigned long long bit_mask = (1LL << i) | (1LL << j);
    x ^= bit_mask;
  }

  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "i", "j"};
  return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                         DefaultComparator{}, param_names);
}
