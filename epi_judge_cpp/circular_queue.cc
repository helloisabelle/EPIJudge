#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

class Queue {
 private:
  std::vector<int> v;
  int tail = -1;
  int head = 0;
  int size = 0;
 public:
  Queue(size_t capacity) {
    for (int i = 0; i < capacity; ++i) v.emplace_back(0);
  }
  void Enqueue(int x) {
    if (tail == -1) tail = 0;
    else if (v.size() == size) {
        std::vector<int> n;
        std::rotate(v.begin(), v.begin() + head, v.end());
        tail = v.size();
        v.emplace_back(0);
        head = 0;
    } else tail = (tail + 1) % v.size();

    v[tail] = x;
    size++;
    return;
  }

  int Dequeue() {
    int save = v[head];
    v[head] = 0;
    if (tail == head) {
      tail = -1;
      head = 0;
    } else head = (head + 1) % v.size();

    size--;
    return save;
  }

  int Size() const {
    return size;
  }
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
