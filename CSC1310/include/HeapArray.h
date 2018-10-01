#if !defined HEAP_ARRAY
#define HEAP_ARRAY

namespace CSC1310
{
template < class T >
class HeapArray
{

   private:
      int max_list;
      T** items;  
      int sze;  
      void heapRebuild();
      void arrayResize(int new_size);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapArray(int (*comp_items) (T* item_1, T* item_2));
      ~HeapArray();

      bool heapIsEmpty();

      //Pre: item represents the data to be inserted into the heap
      //     items that have the same search key are allowed in a heap
      //Post:if the preconditions are met, the item is inserted into the heap according to heap rules
      void heapInsert(T* item);
      //Pre:  none
      //Post: the smallest item in the heap is returned, or NULL if not items are present
      T* heapRemove();
	  T* heapPeek();
};

// this is a MINHEAP (smallest items to top for alphabetical order)
template < class T >
HeapArray<T>::HeapArray(int (*comp_items) (T* item_1, T* item_2))
{ 
   max_list = 2;
   items = new T*[max_list];
   sze = 0;

   compare_items = comp_items;
}  

template < class T >
HeapArray<T>::~HeapArray() 
{ 
   delete[] items;
}  

template < class T >
bool HeapArray<T>::heapIsEmpty() 
{
   return sze == 0;
} 

template < class T >
T* HeapArray<T>::heapPeek()
{
	if (sze == 0) return NULL;
	return items[0];
}

template < class T >
void HeapArray<T>::heapInsert(T* item)
{
   if (sze == max_list) 
   {
      arrayResize(2*max_list); //double the size of the array
   } 

   // place the new item at the end of the heap
   items[sze] = item;

   // trickle new item up to its proper position
   int place = sze;
   int parent = (place - 1)/2; //array location of parent

   while ((parent >= 0) && (*compare_items) (items[place], items[parent]) < 0)
   {
      //swap items[place] and items[parent]
      T* temp = items[parent];
      items[parent] = items[place];
      items[place] = temp;
        
      place = parent;
      parent = (place - 1)/2;
   }  

   sze++;
} 

template < class T >
T* HeapArray<T>::heapRemove()
{
   T* root_item = NULL;
   if (!heapIsEmpty()) 
   {
      root_item = items[0];  //dequeue smallest
      items[0] = items[sze - 1];
      items[sze - 1] = NULL;
      sze--;
      heapRebuild(); 
   }  
   else
   {
      return NULL;
   }

   return root_item;
}  

template < class T >
void HeapArray<T>::heapRebuild() 
{
   bool swap = true;

   int parent = 0;
   int child = 2*parent + 1;  //index of parent's left child, if any

   while (child < sze && swap)
   {
      swap = false;

      //root is not a leaf, so it has a left child at child
      int right_child = child + 1;  //index of right child, if any

      //if parent has a right child, find smaller child
      //note that using a Heap, FIFO order may not be maintained for items with the same priority
      if (right_child < sze)
      {
         if ((*compare_items) (items[right_child], items[child]) < 0)
         {
            child = right_child;  //index of smaller child
         }
      } 

      //if the parent's value is larger than the
      //value in the smaller child, swap values

      if ((*compare_items) (items[parent], items[child]) > 0)
      {
         T* swap_item = items[parent];
         items[parent] = items[child];
         items[child] = swap_item;
         swap = true;
      }

      parent = child;
      child = 2*parent + 1; //if out of bounds, we are done
   }
} 

template < class T >
void HeapArray<T>::arrayResize(int new_size)
{
   max_list = new_size;
   T** temp = new T*[max_list];

   for (int x = 0; x < sze; x++)
   {
      temp[x] = items[x];
   }

   delete[] items;
   items = temp;
}
}

#endif
