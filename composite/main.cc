#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Entry {
public:
  Entry *parent_ = NULL;
  virtual string getName() = 0;
  virtual int getSize() = 0;
  void add(Entry *entry) { cerr << "error" << endl; }
  void ls() { cerr << "error" << endl; }
  string getInfo() {
    return string(getName() + "(" + to_string(getSize()) + ")");
  }
  string getFullName() {
    string fullname;
    Entry *entry = this;
    do {
      fullname = "/" + entry->getName() + fullname;
      entry = entry->parent_;
    } while (entry != NULL);
    return fullname;
  }
};

class File : public Entry {
private:
  string name_;
  int size_;

public:
  File(string name, int size) : name_(name), size_(size) {}
  string getName() { return name_; }
  int getSize() { return size_; }
};

class Directory : public Entry {
private:
  string name_;
  vector<Entry *> directory;

public:
  Directory(string name) : name_(name) {}
  string getName() { return name_; }
  int getSize() {
    int sum = 0;
    for (auto entry : directory) {
      sum += entry->getSize();
    }
    return sum;
  }
  void add(Entry *entry) {
    directory.emplace_back(entry);
    entry->parent_ = this;
  }
  void ls() {
    for (auto entry : directory) {
      cout << entry->getName() << endl;
    }
  }
};

int main() {
  Directory *root = new Directory("root");
  Directory *bin = new Directory("bin");
  Directory *tmp = new Directory("tmp");
  Directory *usr = new Directory("usr");
  root->add(bin);
  root->add(tmp);
  root->add(usr);
  bin->add(new File("vi", 100));
  bin->add(new File("latex", 10));

  root->ls();
  cout << root->getInfo() << endl;
  bin->ls();
  cout << bin->getInfo() << endl;

  Directory *yuki = new Directory("yuki");
  usr->add(yuki);
  File *diary = new File("diary.html", 30000);
  yuki->add(diary);
  yuki->add(new File("memo.tex", 7000));

  //   root->ls();
  //   cout << root->getInfo() << endl;

  //   usr->ls();
  //   cout << usr->getInfo() << endl;

  //   yuki->ls();
  //   cout << yuki->getInfo() << endl;

  cout << yuki->getFullName() << endl;
  cout << diary->getFullName() << endl;

  return 0;
}
