#if !defined HASH_TABLE_AVL
#define HASH_TABLE_AVL

#include "AVLTree.h"
#include <cmath>

namespace CSC1310
{
template < class T >
class HashTableAVL
{

   private:
      AVLTree<T>** hash_table;  
      double adj_max_avg_probes;   
      int sze;  
      int hash_table_size;

      int (*hash_function_item) (T* item);
      int (*hash_function_key) (String* key);

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      int computeRawHashItem(T* item);
      int computeRawHashKey(String* key);
      int computeHashIndex(int raw_hash);
      int nextPrime(int start_search);
      void changeHashTableSize(int new_size);

   public:
      HashTableAVL(int map, int (*hash_function_item) (T* item), int (*hash_function_key) (String* sk), int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~HashTableAVL();

      bool tableIsEmpty();
      int tableSize();
      T* tableRetrieve(String* sk);
      bool tableInsert(T* item);
      bool tableRemove(String* sk);

      //AVLTreeIterator<T>* iterator();  //how could this be written?
};

template < class T >
HashTableAVL<T>::HashTableAVL(int map, int (*hash_item) (T* item), int (*hash_key) (String* sk), int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   hash_table_size = 11;
   hash_table = new AVLTree<T>*[hash_table_size];
   
   //initialize the hash table to contain empty sorted lists
   for (int i = 0; i < hash_table_size; i++)
   {
      hash_table[i] = new AVLTree<T>(comp_items, comp_keys);
   }

   sze = 0;
   adj_max_avg_probes = 1.0/pow(2, map);

   compare_items = comp_items;
   compare_keys = comp_keys;

   hash_function_item = hash_item;
   hash_function_key = hash_key;
}

template < class T >
HashTableAVL<T>::~HashTableAVL()
{
   for (int i = 0; i < hash_table_size; i++)
   {
      delete hash_table[i];
   }

   delete[] hash_table;
}

template < class T >
bool HashTableAVL<T>::tableIsEmpty() 
{
   return (sze == 0);
} 

template < class T >
int HashTableAVL<T>::tableSize() 
{
   return sze;
} 

template < class T >
int HashTableAVL<T>::computeRawHashKey(String* sk)
{
   return (*hash_function_key) (sk);
}

template < class T >
int HashTableAVL<T>::computeRawHashItem(T* item)
{
   return (*hash_function_item) (item);
}

template < class T >
int HashTableAVL<T>::computeHashIndex(int raw_hash)
{
   return raw_hash % hash_table_size;
}

template < class T >
T* HashTableAVL<T>::tableRetrieve(String* sk) 
{
   T* found_key = NULL;
   int current_spot = computeHashIndex(computeRawHashKey(sk));

   found_key = hash_table[current_spot]->retrieve(sk);
   return found_key;
}

template < class T >
bool HashTableAVL<T>::tableInsert(T* item)
{
   bool success = false;
   int min_hash_table_size = (int) sze*adj_max_avg_probes; 
   if (hash_table_size < min_hash_table_size)
   {
      changeHashTableSize(2*hash_table_size);  //don't want to do this too often
   }

   int current_spot = computeHashIndex(computeRawHashItem(item));

   T* found_key = hash_table[current_spot]->retrieve(item->getKey());  //duplicates ignored
   if (found_key == NULL)
   {
      hash_table[current_spot]->insert(item);
      success = true;
      sze++;
   }

   return success;
}

template < class T >
bool HashTableAVL<T>::tableRemove(String* sk) 
{
   bool success = false;
   int current_spot = computeHashIndex(computeRawHashKey(sk));

   T* found_key = hash_table[current_spot]->retrieve(sk);
   if (found_key != NULL)
   {
      hash_table[current_spot]->remove(sk);
      success = true;
      sze--;
   }

   return success;
}

template < class T >
void HashTableAVL<T>::changeHashTableSize(int start_size)
{
//cout << sze << endl;

   AVLTree<T>** old_table = hash_table;
   int old_table_size = hash_table_size;

   //create the larger temporary array
   hash_table_size = nextPrime(start_size);
//cout << "resizing to " << hash_table_size << endl;
   hash_table = new AVLTree<T>*[hash_table_size];

   //it is possible to use tableInsert to perform the resizing, but size must be set to 0
   sze = 0;  //important

   for (int i = 0; i < hash_table_size; i++)
   {
      hash_table[i] = new AVLTree<T>(compare_items, compare_keys);
   }

   for (int i = 0; i < old_table_size; i++)
   {
      AVLTreeIterator<T>* iter = old_table[i]->iterator();
      iter->setPostorder();  //level order really only useful for adaptable binary search tree
                              //in which case all level 0s moved first, then all level 1s, etc.
      while(iter->hasNext())
      {
         T* item = iter->next();
         tableInsert(item);
      }
      delete iter;
   }

   for (int i = 0; i < old_table_size; i++)
   {
      delete old_table[i];
   }
   delete[] old_table;
}

template < class T >
//start search is an even number
int HashTableAVL<T>::nextPrime(int start_search)
{
   bool test_bool; //is the current trial number prime?
   int _sqrt;
   int prime = start_search + 1;  //obtain an odd number to test for primeness

   do
   {
      test_bool = true;  //assume a prime number until proven otherwise

      _sqrt = ((int) sqrt(prime)) + 1;
      for (int i = 2; i < _sqrt; i++)
      {
         if (prime % i == 0)  //if not a prime number, break out of the inner for loop
         {
            test_bool = false;
            break;
         }
      }

      prime = prime + 2;  //next odd number
   } while (!test_bool);

   return prime - 2;  //a successful prime number will be too large at this point
}
}

#endif
