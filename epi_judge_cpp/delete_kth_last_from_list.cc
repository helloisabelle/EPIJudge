#include <memory>
#include <iostream>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  auto dummy_head = make_shared<ListNode<int>>(0, L);
  shared_ptr<ListNode<int>> k_it, it, prev;
  it = dummy_head;
  k_it = L;

  while (k--) k_it = k_it->next;

  while (k_it != nullptr) {
    it = it->next;
    k_it = k_it->next;
  }

  it->next = it->next->next;

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
