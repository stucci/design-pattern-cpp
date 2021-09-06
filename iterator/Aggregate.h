/************************************************************************/
/* Aggregate.h                                                          */
/************************************************************************/
#ifndef MY_DATACOLLECTION_HEADER
#define MY_DATACOLLECTION_HEADER
#include "Iterator.h"

template <class T>
class aggregate {
  friend class Iterator<T, aggregate>;

 public:
  void add(T a) { m_data.push_back(a); }
  Iterator<T, aggregate> *create_iterator() {
    return new Iterator<T, aggregate>(this);
  }

 private:
  std::vector<T> m_data;
};

#endif