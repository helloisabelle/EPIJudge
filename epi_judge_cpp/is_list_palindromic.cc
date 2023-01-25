#include "list_node.h"
#include "test_framework/generic_test.h"

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  auto fast = L, slow = L;
  shared_ptr<ListNode<int>> prev = nullptr;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  while (slow) {
    auto save = slow->next;
    slow->next = prev;
    prev = slow;
    if (save == nullptr) break;
    slow = save;
  }

  while (slow) {
    if (L->data != slow->data) return false;
    L = L->next;
    slow = slow->next;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
