#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
 public:
  virtual void use() = 0;
};

class Factory {
 public:
  Product* create(string owner) {  // template method
    Product* p = createProduct(owner);
    registerProduct(p);
    return p;
  }

 protected:
  virtual Product* createProduct(string owner) = 0;    // factory method
  virtual void registerProduct(Product* product) = 0;  // factory method
};

class IDCard : public Product {
 public:
  IDCard(string owner) : owner_(owner) {}
  void use() { cout << "use " << owner_ << " card." << endl; }
  string getOwner() { return owner_; };

 private:
  string owner_;
};

class IDCardFactory : public Factory {
 protected:
  Product* createProduct(string owner) { return new IDCard(owner); }
  void registerProduct(Product* product) {
    owners_.emplace_back(dynamic_cast<IDCard*>(product)->getOwner());
  }

 private:
  vector<string> owners_;
};

int main() {
  Factory* f = new IDCardFactory();
  Product* p1 = f->create("John Doe");
  Product* p2 = f->create("God");
  p1->use();
  p2->use();
  return 0;
}
