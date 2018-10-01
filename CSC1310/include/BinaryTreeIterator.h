#if !defined BINARY_TREE_ITERATOR
#define BINARY_TREE_ITERATOR

#include "TreeNode.h"
#include "QueueArray.h"

namespace CSC1310
{
template < class T >
class BinaryTreeIterator
{
   private:
      CSC1310::QueueArray<T>* q;
      TreeNode<T>* root;

      void inorder(TreeNode<T>* tNode);
      void preorder(TreeNode<T>* tNode);
      void postorder(TreeNode<T>* tNode);

   public:
      BinaryTreeIterator(TreeNode<T>* root);
      ~BinaryTreeIterator();

      bool hasNext();
      T* next();

      void setInorder();
      void setPreorder();
      void setPostorder();
};

template < class T >
BinaryTreeIterator<T>::BinaryTreeIterator(TreeNode<T>* r)
{
   q = new CSC1310::QueueArray<T>();
   root = r;
}

template < class T >
BinaryTreeIterator<T>::~BinaryTreeIterator()
{
   delete q;
}

template < class T >
bool BinaryTreeIterator<T>::hasNext()
{
   return (!q->isEmpty());
}

template < class T >
T* BinaryTreeIterator<T>::next()
{
   T* item = NULL;
   if (hasNext())
   {
      item = q->dequeue();
   }
   return item;
}

template < class T >
void BinaryTreeIterator<T>::setInorder()
{
   q->dequeueAll();
   inorder(root);
}

template < class T >
void BinaryTreeIterator<T>::inorder(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      inorder(tNode->getLeft());
      q->enqueue(tNode->getItem());
      inorder(tNode->getRight());
   }
}

template < class T >
void BinaryTreeIterator<T>::setPreorder()
{
   q->dequeueAll();
   preorder(root);
}

template < class T >
void BinaryTreeIterator<T>::preorder(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      q->enqueue(tNode->getItem());
      preorder(tNode->getLeft());
      preorder(tNode->getRight());
   }
}

template < class T >
void BinaryTreeIterator<T>::setPostorder()
{
   q->dequeueAll();
   postorder(root);
}

template < class T >
void BinaryTreeIterator<T>::postorder(TreeNode<T>* tNode)
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
