#include <iterator>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

struct Person {
  int age;
  string name;
};

void GroupByAge(vector<Person>* people) {
  std::vector<Person>& p = *people;
  std::unordered_map<int, int> count, index;

  std::vector<int> visited(p.size(), 0);

  for (int i = 0; i < p.size(); ++i) ++count[p[i].age];
  int i = 0;
  for (auto x : count) {
    index[x.first] = i;
    i += x.second;
  }

//  int j = 0;
//  while (j < p.size()) {
//    while (!visited[j]) {
//      int save = p[j].age;
//      std::swap(p[j], p[index[p[j].age]]);
//      ++visited[index[save]];
//      ++index[save];
//    }
//    ++j;
//  }

  while (!empty(index)) {
    auto curr = begin(index);
    auto move = index.find(p[curr->second].age);
    std::swap(p[curr->second], p[move->second]);
    if (--count[move->first] > 0) ++move->second;
    // we filled this sub arr
    else index.erase(move);
  }
  return;
}

namespace test_framework {
template <>
struct SerializationTrait<Person> : UserSerTrait<Person, int, string> {};
}  // namespace test_framework

void GroupByAgeWrapper(TimedExecutor& executor, vector<Person>& people) {
  if (people.empty()) {
    return;
  }
  std::multiset<Person, std::function<bool(Person, Person)>> values(
      begin(people), end(people), [](const Person& a, const Person& b) {
        return a.age == b.age ? a.name < b.name : a.age < b.age;
      });

  executor.Run([&] { GroupByAge(&people); });

  if (people.empty()) {
    throw TestFailure("Empty result");
  }

  std::set<int> ages;
  int last_age = people[0].age;
  for (auto& x : people) {
    if (ages.count(x.age)) {
      throw TestFailure("Entries are not grouped by age");
    }
    if (x.age != last_age) {
      ages.insert(last_age);
      last_age = x.age;
    }
    auto it = values.find(x);
    if (it == end(values)) {
      throw TestFailure("Entry set changed");
    }
    values.erase(it);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "people"};
  return GenericTestMain(args, "group_equal_entries.cc",
                         "group_equal_entries.tsv", &GroupByAgeWrapper,
                         DefaultComparator{}, param_names);
}
