#include <iostream>
#include <string>
using namespace std;

class AbstractProductA {
public:
  virtual string usefulFunctionA() const = 0;
};

class ConcreteProductA : public AbstractProductA {
public:
  string usefulFunctionA() const override { return "ProductA function!"; }
};

class AbstractProductB {
public:
  virtual string usefulFunctionB() const = 0;
};

class ConcreteProductB : public AbstractProductB {
public:
  string usefulFunctionB() const override { return "ProductB function!"; }
};

class AbstractFactory {
public:
  virtual AbstractProductA *CreateProductA() const = 0;
  virtual AbstractProductB *CreateProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA();
  }
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB();
  }
};

void createByAbstractFactory(AbstractFactory *f) {
  const AbstractProductA *pa = f->CreateProductA();
  const AbstractProductB *pb = f->CreateProductB();
  cout << pa->usefulFunctionA() << endl;
  cout << pb->usefulFunctionB() << endl;
}

int main() {
  ConcreteFactory1 *f1 = new ConcreteFactory1();
  createByAbstractFactory(f1);
  return 0;
}
