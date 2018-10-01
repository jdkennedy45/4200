#if !defined LIST_DOUBLY_LINKED
#define LIST_DOUBLY_LINKED

#include "DoubleNode.h"
#include "ListDoublyLinkedIterator.h"

namespace CSC1310
{
template < class T >
class ListDoublyLinked
{

   private:
      DoubleNode<T>* loc;
      int loc_pos;
      int sz;

      DoubleNode<T>* find(int index);

   public:
      ListDoublyLinked();
      ~ListDoublyLinked();

      bool isEmpty();
      int size();
      void removeAll(); 
      T* get(int index);
      void add(T* item);
      void add(int index, T* item);
      void remove(int index);

      ListDoublyLinkedIterator<T>* iterator();

};

template < class T >
void ListDoublyLinked<T>::removeAll() 
{
   if (sz > 0)
   {
       DoubleNode<T>* prev = find(1); 
       DoubleNode<T>* curr = prev->getNext();

       //need to remove all previous links to prevent memory leak
       while (curr != NULL)
       {
          curr->setPrev(NULL);
          delete prev;
          prev = curr;
          curr = curr->getNext();
       }
       delete prev;
   }

   loc = NULL;
   loc_pos = 0;
   sz = 0;
}

template < class T >
ListDoublyLinked<T>::ListDoublyLinked() 
{
   sz = 0;
   removeAll();
} 

template < class T >
ListDoublyLinked<T>::~ListDoublyLinked()
{
   removeAll();
}

template < class T >
bool ListDoublyLinked<T>::isEmpty() 
{
   return sz == 0;
} 

template < class T >
int ListDoublyLinked<T>::size() 
{
   return sz;
}

template < class T >
T* ListDoublyLinked<T>::get(int index)
{
   if (index >= 1 && index <= sz) 
   {
      DoubleNode<T>* curr = find(index);
      T* item = curr->getItem();
      loc = curr;  //stay at location of most recent activity
      loc_pos = index;
      return item;
   }

   return NULL;
}


template < class T >
DoubleNode<T>* ListDoublyLinked<T>::find(int index)
{
   //this check needed for the iterator method
   if (sz == 0)  //need to check the size before entering the loops
   { 
      return NULL;
   }

   DoubleNode<T>* where = loc;
   if (loc_pos <= index)  //go later in list
   {
      //this loop causes a problem if locPos = 0 (see check at the top of this method)
      //not a problem with LRB, however
      for (int skip = loc_pos; skip < index; skip++) 
      {
         where = where->getNext();
      } 
   }
   else  //go earlier in list
   {
      for (int skip = loc_pos; skip > index; skip--)
      {
         where = where->getPrev();
      }
   }

   return where;
}

template < class T >
void ListDoublyLinked<T>::add(T* item)
{
   add(size() + 1, item);
}

template < class T >
void ListDoublyLinked<T>::add(int index, T* item)
{
   if (index >= 1 && index <= sz + 1) 
   {
      DoubleNode<T>* node = new DoubleNode<T>(item);
      if (index == 1) 
      {
         DoubleNode<T>* curr = NULL;
         if (sz > 0)
         {
            curr = find(1);
            curr->setPrev(node);
         }

         node->setNext(curr);
         loc = node;
         loc_pos = 1;
      } 
      else 
      {
         DoubleNode<T>* prev = find(index - 1);
         DoubleNode<T>* curr = prev->getNext();  //could be null (can't set a prev link)

         node->setNext(curr);
         node->setPrev(prev);
         prev->setNext(node);

         if (curr != NULL)  //check for end of list
         {
            curr->setPrev(node);
         }

         loc = node;
         loc_pos = index;
       } 
       sz++;
    }
}

template < class T >
void ListDoublyLinked<T>::remove(int index) 
{
   if (index >= 1 && index <= sz) //at least one item in the list
   {
      if (index == 1) 
      {
         DoubleNode<T>* prev = find(1);
         DoubleNode<T>* curr = prev->getNext();

         if (curr != NULL)  //more than one item in the list
         {
            curr->setPrev(NULL);
            loc_pos = 1;
            delete prev;
         }
         else  //only one item in the list
         {
            loc_pos = 0;
            delete prev;
         }

         loc = curr;
      } 
      else 
      {
         DoubleNode<T>* prev = find(index - 1);
         DoubleNode<T>* curr = prev->getNext();
         DoubleNode<T>* after = curr->getNext();  //could be null if deleting last item in list
         prev->setNext(after);

         if (after != NULL)  // not deleting last item in list
         {
            after->setPrev(prev);
         }

         loc = prev;
         loc_pos = index - 1;
         delete curr;
      } 
      sz--;
   }
}  

template < class T >
ListDoublyLinkedIterator<T>* ListDoublyLinked<T>::iterator()
{
   //locate the head/first node for the iterator without moving the interior node (loc)
   DoubleNode<T>* head = find(1);
   ListDoublyLinkedIterator<T>* iter = new ListDoublyLinkedIterator<T>(head);
   return iter;
} 
}

#endif
