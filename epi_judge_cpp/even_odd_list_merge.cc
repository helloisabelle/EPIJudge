#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  auto dummy_head = make_shared<ListNode<int>>(0, L);
  shared_ptr<ListNode<int>> even = L;
  shared_ptr<ListNode<int>> odd = L ? L->next : nullptr;
  shared_ptr<ListNode<int>> odd_save = odd;

  while (even && odd) {
    even->next = odd->next;
    odd->next = odd->next ? odd->next->next : nullptr;
    if (!even->next) break;
    even = even->next;
    odd = odd->next;
  }

  if (even) even->next = odd_save;
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
