#if !defined AVL_TREE_ITERATOR
#define AVL_TREE_ITERATOR

#include "QueueArray.h"
#include "AVLTreeNode.h"

namespace CSC1310
{
template < class T >
class AVLTreeIterator
{

   private:
      QueueArray<T>* q;
      AVLTreeNode<T>* root;

      void inorder(AVLTreeNode<T>* tNode);
      void preorder(AVLTreeNode<T>* tNode);
      void postorder(AVLTreeNode<T>* tNode);

   public:
      ~AVLTreeIterator();
      AVLTreeIterator(AVLTreeNode<T>* root);

      bool hasNext();
      T* next();

      void setInorder();
      void setPreorder();
      void setPostorder();

};

template < class T >
AVLTreeIterator<T>::AVLTreeIterator(AVLTreeNode<T>* root)
{
   q = new QueueArray<T>();
   this->root = root;
}

template < class T >
AVLTreeIterator<T>::~AVLTreeIterator()
{
   delete q;
}

template < class T >
bool AVLTreeIterator<T>::hasNext()
{
   return (!q->isEmpty());
}

template < class T >
T* AVLTreeIterator<T>::next()
{
   if (hasNext())
   {
      return q->dequeue();
   }
}

template < class T >
void AVLTreeIterator<T>::setInorder()
{
   q->dequeueAll();
   inorder(root);
}

template < class T >
void AVLTreeIterator<T>::inorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      inorder(tNode->getLeft());
      q->enqueue(tNode->getItem());
      inorder(tNode->getRight());
   }
}

template < class T >
void AVLTreeIterator<T>::setPreorder()
{
   q->dequeueAll();
   preorder(root);
}

template < class T >
void AVLTreeIterator<T>::preorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      q->enqueue(tNode->getItem());
      preorder(tNode->getLeft());
      preorder(tNode->getRight());
   }
}

template < class T >
void AVLTreeIterator<T>::setPostorder()
{
   q->dequeueAll();
   postorder(root);
}

template < class T >
void AVLTreeIterator<T>::postorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      postorder(tNode->getLeft());
      postorder(tNode->getRight());
      q->enqueue(tNode->getItem());
   }
}
}

#endif
