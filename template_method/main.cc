#include <iostream>
#include <string>
using namespace std;

class AbstractDisplay {
 public:
  virtual void open() const = 0;
  virtual void print() const = 0;
  virtual void close() const = 0;
  void display() const {  // template method
    open();
    print();
    print();
    print();
    print();
    print();
    close();
  }
};

class CharDisplay : public AbstractDisplay {
 public:
  CharDisplay(char c) : c_(c){};
  void open() const { cout << "-- open char --" << endl; }
  void print() const { cout << c_ << endl; }
  void close() const { cout << "-- close char --" << endl; }

 private:
  char c_;
};

class StringDisplay : public AbstractDisplay {
 public:
  StringDisplay(string s) : s_(s){};
  void open() const { cout << "-- open string --" << endl; }
  void print() const { cout << s_ << endl; }
  void close() const { cout << "-- close string --" << endl; }

 private:
  string s_;
};

int main() {
  AbstractDisplay *cd = new CharDisplay('a');
  AbstractDisplay *sd = new StringDisplay("str");
  cd->display();
  sd->display();
  delete cd;
  delete sd;
  return 0;
}
