#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book;

class Iterator {
 public:
  virtual bool const hasNext() = 0;
  virtual Book next() = 0;
};

class Aggregate {
 public:
  virtual Iterator *iterator() = 0;
};

class Book {
 private:
  string name_;

 public:
  void setName(string name) { name_ = name; }
  string getName() { return name_; }
};

class BookShelf : public Aggregate {
 private:
  vector<Book> books_;
  int last_;

 public:
  BookShelf(int maxSize) : last_(0) { books_.resize(maxSize); }
  Book getBookAt(int index) { return books_[index]; }
  void appendBook(Book book) {
    books_[last_] = book;
    last_++;
  }
  int getLength() { return last_; }
  Iterator *iterator();
};

class BookShelfIterator : public Iterator {
 private:
  BookShelf bookShelf_;
  int index_;

 public:
  BookShelfIterator(BookShelf bookShelf) : index_(0), bookShelf_(bookShelf) {}
  bool const hasNext() {
    if (index_ < bookShelf_.getLength()) {
      return true;
    }
    return false;
  }
  Book next() {
    Book book = bookShelf_.getBookAt(index_);
    index_++;
    return book;
  }
};

Iterator *BookShelf::iterator() { return new BookShelfIterator(*this); }

int main() {
  BookShelf bookShelf(5);

  Book book1;
  book1.setName("Bible");
  bookShelf.appendBook(book1);

  Book book2;
  book2.setName("CISP");
  bookShelf.appendBook(book2);

  Book book3;
  book3.setName("GoF");
  bookShelf.appendBook(book3);

  Iterator *itr = bookShelf.iterator();
  while (itr->hasNext()) {
    cout << itr->next().getName() << endl;
  }

  return 0;
}