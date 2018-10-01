#if !defined TABLE_AVL
#define TABLE_AVL

#include "AVLTree.h"

namespace CSC1310
{
template < class T >
class TableAVL
{

   private:
      AVLTree<T>* avl_tree;

   public:
      TableAVL(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~TableAVL();

      bool tableIsEmpty();
      int tableSize();
      void tableInsert(T* item);
      void tableRemove(String* sk);
      T* tableRetrieve(String* sk);
      AVLTreeIterator<T>* iterator();
      
};

template < class T >
TableAVL<T>::TableAVL(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item)) 
{
   avl_tree = new AVLTree<T>(comp_items, comp_keys);
}  

template < class T >
TableAVL<T>::~TableAVL() 
{ 
   delete avl_tree;
}  

template < class T >
bool TableAVL<T>::tableIsEmpty() 
{
   return avl_tree->isEmpty();
}

template < class T >
int TableAVL<T>::tableSize() 
{
   return avl_tree->size();
} 

template < class T >
void TableAVL<T>::tableInsert(T* item)
{
   avl_tree->insert(item);
} 

template < class T >
void TableAVL<T>::tableRemove(String* sk)
{
   avl_tree->remove(sk);
}

template < class T >
T* TableAVL<T>::tableRetrieve(String* sk)
{
   return avl_tree->retrieve(sk);
}

template < class T >
AVLTreeIterator<T>* TableAVL<T>::iterator()
{
   AVLTreeIterator<T>* avl_iter = avl_tree->iterator();
   avl_iter->setInorder();
   return avl_iter;
}
}

#endif
