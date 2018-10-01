#if !defined LIST_DOUBLY_LINKED_ITERATOR
#define LIST_DOUBLY_LINKED_ITERATOR

#include "DoubleNode.h"

namespace CSC1310
{
template < class T >
class ListDoublyLinkedIterator
{

   private:
      DoubleNode<T>* ref;

   public:
      ListDoublyLinkedIterator(DoubleNode<T>* head);
      ~ListDoublyLinkedIterator();
      bool hasNext();
      T* next();

};

template < class T >
ListDoublyLinkedIterator<T>::ListDoublyLinkedIterator(DoubleNode<T>* first)
{
   ref = first;
}

template < class T >
ListDoublyLinkedIterator<T>::~ListDoublyLinkedIterator()
{
   ref = NULL;
}

template < class T >
bool ListDoublyLinkedIterator<T>::hasNext()
{
   return ref != NULL;
}

template < class T >
T* ListDoublyLinkedIterator<T>::next()
{
   T* item = NULL;

   if (hasNext())
   {
      item = ref->getItem();
      ref = ref->getNext();
   }

   return item;
}
}

#endif
