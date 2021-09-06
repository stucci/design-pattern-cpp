/************************************************************************/
/* Iterator.h                                                           */
/************************************************************************/
#ifndef MY_ITERATOR_HEADER
#define MY_ITERATOR_HEADER

#include <iterator>
#include <vector>

//////////////////////////////////////////////////////////////////////////
template <class T, class U>
class Iterator {
 public:
  typedef typename std::vector<T>::iterator iter_type;
  Iterator(U *pData) : m_pData(pData) { m_it = m_pData->m_data.begin(); }
  void first() { m_it = m_pData->m_data.begin(); }
  void next() { m_it++; }
  bool isDone() { return (m_it == m_pData->m_data.end()); }
  iter_type current() { return m_it; }

 private:
  U *m_pData;
  iter_type m_it;
};

#endif