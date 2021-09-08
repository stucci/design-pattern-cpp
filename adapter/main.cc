#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Target {
public:
  virtual string Request() const {
    return "Target: The default target's behavior.";
  }
};

class Adaptee {
public:
  string SpecificRequet() const { return ".eetpadA eht fo roivaheb laicepS"; }
};

class Adapter : public Target {
private:
  Adaptee *adaptee_;

public:
  Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
  string Request() const override {
    string ret = adaptee_->SpecificRequet();
    reverse(ret.begin(), ret.end());
    return "Adapter (TRANSLATED): " + ret;
  }
};

int main() {
  Adaptee *adaptee = new Adaptee();
  Target *adapter = new Adapter(adaptee);
  cout << adapter->Request() << endl;
  return 0;
}
