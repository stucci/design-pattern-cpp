#include <iostream>
using namespace std;

class Singleton final { // final keyword
private:
  Singleton() = default;
  ~Singleton() = default;

public:
  Singleton(const Singleton &) = delete;            // copy constructor
  Singleton &operator=(const Singleton &) = delete; // copy assignment operator
  Singleton(Singleton &&) = delete;                 // move constructor
  Singleton &operator=(Singleton &) = delete;       // move assignment operator
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }
};

// class DerivedSingleton : public Singleton {
// }  // compile error occurs, thanks to `final` keyword.

int main() {
  Singleton &s1 = Singleton::getInstance();
  Singleton &s2 = Singleton::getInstance();
  // compile error occurs, thanks to private constructor
  // Singleton *s = new Singleton();
  cout << &s1 << endl;
  cout << &s2 << endl;
  if (&s1 == &s2)
    cout << "same!" << endl;
  return 0;
}
