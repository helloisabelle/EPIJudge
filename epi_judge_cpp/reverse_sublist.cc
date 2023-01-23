#include "list_node.h"
#include "test_framework/generic_test.h"
#include <iostream>

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  auto dummy_head = make_shared<ListNode<int>>(0, L);
  shared_ptr<ListNode<int>> before_s = dummy_head;

  int i = 1;

  while (i <= start - 1) {
    if (i == start - 1)  before_s = L;
    L = L->next;
    i++;
  }

  auto p = before_s->next;
//  while (start++ < finish) {
//    auto temp = p->next; // set to next element
//    p->next = temp->next; // save curr's next element which we will see next
//    temp->next = before_s->next; // before_s->next points at element before temp
//    before_s->next = temp; // curr element
//  }
//

  while (start++ < finish) {
    auto curr = p->next;
    p->next = curr->next;
    curr->next = before_s->next;
    before_s->next = curr;
  }

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
