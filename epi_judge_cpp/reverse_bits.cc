#include "test_framework/generic_test.h"
#include <iostream>

unsigned long long ReverseBits(unsigned long long x) {
  // TODO - you fill in here.
  unsigned long long ans = x;

  for (int i = 0, j = 63; i <= 63/2 && j >= 63/2 && i != j; i++, j--){
      if (((x >> i) & 1) != ((x >> j) & 1)) {
          // 1L = 1 long long
          unsigned long long bit_mask = (1LL << i) | (1LL << j);
              ans ^= bit_mask;
      }
  }

  // Do look up table for faster compute. O(n/L). L = len n = partition size

//  const int mask_size = 16;
//  const int bit_mask = 0xFFFF;
//  // isolate lowest 16 bit then shift to 64 index
//  return look_up[x & bit_mask] << (3 * mask_size) |
//  look_up[(x >> mask_size) & bit_mask] << (2 * mask_size) |
//  look_up[(x >> (mask_size * 2)) & bit_mask] << mask_size |
//  look_up[(x >> (mask_size * 3)) & bit_mask]


  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
