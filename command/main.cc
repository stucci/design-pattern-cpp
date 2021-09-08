#include <iostream>
#include <string>
using namespace std;

class Command {
public:
  virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
private:
  string pay_load_;

public:
  explicit SimpleCommand(string pay_load) : pay_load_(pay_load) {}
  void Execute() const override {
    cout << "SimpleCommand: See, I can do simple things like printing ("
         << this->pay_load_ << ")\n";
  }
};

class Receiver {
public:
  void DoSomething(const string &a) {
    cout << "Receiver: Working on (" << a << ".)\n";
  }
  void DoSomethingElse(const string &b) {
    cout << "Receiver: Also working on (" << b << ".)\n";
  }
};

class Invoker {
private:
  Command *on_start_;
  Command *on_finish_;

public:
  void SetOnStart(Command *command) { this->on_start_ = command; }
  void SetOnFinish(Command *command) { this->on_finish_ = command; }
  void DoSomethingImportant() {
    if (this->on_start_) {
      this->on_start_->Execute();
    }
    if (this->on_finish_) {
      this->on_finish_->Execute();
    }
  }
};

int main() {
  Invoker *invoker = new Invoker;
  invoker->SetOnStart(new SimpleCommand("Say Hi!"));
  invoker->SetOnFinish(new SimpleCommand("Say Good Bye!"));
  invoker->DoSomethingImportant();
  return 0;
}
