#include <memory>
#include <iostream>

#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L) {
  auto dummy_head = make_shared<ListNode<int>>(0, L);
  auto fast = L, slow = L, prev = dummy_head;

  if (L == nullptr || L->next == nullptr) return L;

  while (fast && fast->next) {
    prev = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  prev->next = nullptr;

  auto tail = dummy_head;

  L = StableSortList(L);
  slow = StableSortList(slow);
  auto slow_head = slow;

  while (L != slow_head && L && slow) {
    if (L->data < slow->data) {
      tail->next = L;
      tail = L;
      L = L->next;
    } else {
      tail->next = slow;
      tail = slow;
      slow = slow->next;
    }
  }

  if (L && L != slow_head) {
    tail->next = L;
    tail = L;
  } else if (slow) {
    tail->next = slow;
    tail = slow;
  }

//  while (L && L->next) {
//    auto copy = L;
//    shared_ptr<ListNode<int>> min = nullptr;
//    auto before_copy = dummy_head;
//    while (copy->next) {
//      if (copy->next->data < L->data) {
//        if (min == nullptr || copy->next->data < min->data) {
//          before_copy = copy;
//          min = copy->next;
//        }
//      }
//
//      copy = copy->next;
//    }
//
//    if (min != nullptr) {
//      before_copy->next = L;
//      auto slow_head = L->next;
//      L->next = min->next;
//      before->next = min;
//      min->next = slow_head;
//      before = min;
//      L = min->next;
//    } else {
//      before = L;
//      L = L->next;
//    }
//  }
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
