#if !defined PQ_HEAP
#define PQ_HEAP

#include "HeapArray.h"

namespace CSC1310
{
template < class T >
class PQHeap
{
   private:
      HeapArray<T>* ha;

   public:
      PQHeap(int (*compare_item) (T* item_1, T* item_2));
      ~PQHeap();

      bool pqIsEmpty();
      void pqInsert(T* item);
      T* pqRemove();
	  T* pqPeek();
};

template < class T >
PQHeap<T>::PQHeap(int (*compare_item) (T* item_1, T* item_2))
{
   ha = new HeapArray<T>(compare_item);
}

template < class T >
PQHeap<T>::~PQHeap()
{
   delete ha;
}

template < class T >
bool PQHeap<T>::pqIsEmpty()
{
   return ha->heapIsEmpty();
}

template < class T >
void PQHeap<T>::pqInsert(T* item)
{
   ha->heapInsert(item);
}

template < class T >
T* PQHeap<T>::pqRemove()
{
   T* item = ha->heapRemove();
   return item;
}

template < class T >
T* PQHeap<T>::pqPeek()
{
   T* item = ha->heapPeek();
   return item;
}
}

#endif
