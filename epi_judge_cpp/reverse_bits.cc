#include "test_framework/generic_test.h"
#include <iostream>
#include <limits.h>
#include <unordered_map>

std::unordered_map<unsigned long long, unsigned long long> look_up;

void init() {
  const int mask_size = 16;
  const int bit_mask = 0xFFFF;

  for (unsigned long long z = 0; z <= USHRT_MAX; z++) {
    unsigned long long ans = z;
    for (int i = 0, j = mask_size - 1; i <= (mask_size - 1)/2 && j >= (mask_size - 1)/2 && i != j; i++, j--){
      if (((z >> i) & 1) != ((z >> j) & 1)) {
          // 1L = 1 long long
          unsigned long long mask = (1L << i) | (1L << j);
          ans ^= mask;
      }
    }
    look_up[z] = ans;
  }
}

unsigned long long ReverseBits(unsigned long long x) {
  // isolate lowest 16 bit then shift to 64 index
  return look_up[x & bit_mask] << (3 * mask_size) |
  look_up[(x >> mask_size) & bit_mask] << (2 * mask_size) |
  look_up[(x >> (mask_size * 2)) & bit_mask] << mask_size |
  look_up[(x >> (mask_size * 3)) & bit_mask];
}

int main(int argc, char* argv[]) {
  init();
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
