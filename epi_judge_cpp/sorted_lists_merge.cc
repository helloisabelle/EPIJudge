#include "list_node.h"
#include "test_framework/generic_test.h"
#include <iostream>
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  if (L1 == nullptr) return L2;
  else if (L2 == nullptr) return L1;

  shared_ptr<ListNode<int>> ans = L1;
  if (L1.get()->data > L2.get()->data) ans = L2;

  shared_ptr<ListNode<int>> tail;

  while (L1 != nullptr && L2 != nullptr) {
    if (L1->data <= L2->data) {
      if (tail != nullptr) tail->next = L1;
      tail = L1;
      L1 = L1->next;
    } else {
      if (tail != nullptr) tail->next = L2;
      tail = L2;
      L2 = L2->next;
    }
  }

  tail->next = L1 ? L1 : L2;

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
