/************************************************************************/
/* Iterator Test.cpp                                                    */
/************************************************************************/
#include <iostream>
#include <string>

#include "Aggregate.h"

using namespace std;

class Money {
 public:
  Money(int a = 0) : m_data(a) {}
  void SetMoney(int a) { m_data = a; }
  int GetMoney() { return m_data; }

 private:
  int m_data;
};

class Name {
 public:
  Name(string name) : m_name(name) {}
  const string &GetName() const { return m_name; }
  friend ostream &operator<<(ostream &out, Name name) {
    out << name.GetName();
    return out;
  }

 private:
  string m_name;
};

int main() {
  // sample 1
  cout << "___Iterator with int___" << endl;
  aggregate<int> agg;
  for (int i = 0; i < 10; i++) {
    agg.add(i);
  }
  Iterator<int, aggregate<int>> *it = agg.create_iterator();
  for (it->first(); !it->isDone(); it->next()) {
    cout << *it->current() << endl;
  }

  // sample 2
  cout << "___Iterator with Class Money___" << endl;
  aggregate<Money> agg2;
  Money a(100), b(102), c(10000);
  agg2.add(a);
  agg2.add(b);
  agg2.add(c);
  Iterator<Money, aggregate<Money>> *it2 = agg2.create_iterator();
  for (it2->first(); !it2->isDone(); it2->next()) {
    cout << it2->current()->GetMoney() << endl;
  }
}
