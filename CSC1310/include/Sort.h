#if !defined SORT_H
#define SORT_H

#include <iostream>
using namespace std;

template < class T >
class Sort
{

   private:

      static void _heapSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static void _heapRebuild(T** items, int root, int unsorted_end, int (*compare) (T* one, T* two));

      static void _selectionSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static void _mergeSort(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void merge(T** items, int first, int mid, int last, int (*compare) (T* one, T* two));
      static void choosePivot(T** items, int first, int last);
      static int partition(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void _quickSort(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void _insertionSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static int insertLocation(T** items, T* item, int last, int (*compare) (T* one, T* two));
      static void _insertionBinarySort(T** items, int num_items, int (*compare) (T* one, T* two));

      static int linearSearch(T** items, int num_items, T* item, int index, int (*compare) (T* one, T* two));
      static int binarySearch(T** items, int num_items, T* item, int first, int last, int (*compare) (T* one, T* two));

   public:

      static T** heapSort(T** items, int num_items, int (*compare) (T* one, T* two));

      static T** selectionSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static T** insertionSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static T** mergeSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static T** quickSort(T** items, int num_items, int (*compare) (T* one, T* two));
      static T** insertionBinarySort(T** items, int num_items, int (*compare) (T* one, T* two));

      static int linearSearch(T** items, int num_items, T* item, int (*compare) (T* one, T* two));
      static int binarySearch(T** items, int num_items, T* item, int (*compare) (T* one, T* two));

};

template < class T >
T** Sort<T>::selectionSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   //passes the address of the function via compare
   _selectionSort(sorted, num_items, compare);
   return sorted;
}

template < class T >
void Sort<T>::_selectionSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   for (int spot = 0; spot < num_items - 1; spot++)                   
   {
      int min = spot;                                                   
      for (int scan = spot + 1; scan < num_items; scan++)             
      {
         //dereferences compare (calls the function)
         if ((*compare) (items[scan], items[min]) < 0)               
         {
            min = scan;                                             
         }
      }

      // Swap the values
      T* item = items[min];                                             
      items[min] = items[spot];
      items[spot] = item;
   }
}

template < class T >
T** Sort<T>::insertionSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   _insertionSort(sorted, num_items, compare);
   return sorted;
}

template < class T >
void Sort<T>::_insertionSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   for (int spot = 1; spot < num_items; spot++)
   {
      T* temp = items[spot];
      int position = spot;

      // shift larger values to the right
      while (position > 0 && (*compare) (items[position - 1], temp) > 0)
      {
         items[position] = items[position - 1];
         position--;
      }
            
      items[position] = temp;
   }
}

template < class T >
T** Sort<T>::mergeSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   //could create the temp array needed by merge here and pass it around
   _mergeSort(sorted, 0, num_items - 1, compare);
   return sorted;
}

template < class T >
void Sort<T>::_mergeSort(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   if (first < last) 
   {
      // sort each half
      int mid = first + (last - first)/2;  // index of midpoint

      // sort left half sort[first..mid]
      _mergeSort(items, first, mid, compare);

      // sort right half sort[mid + 1..last]   
      _mergeSort(items, mid + 1, last, compare);  
 
      // merge the two halves
      merge(items, first, mid, last, compare);
   } 
}  

template < class T >
void Sort<T>::merge(T** items, int first, int mid, int last, int (*compare) (T* one, T* two)) 
{
   //tempArray
   T** temp = new T*[last - first + 1];
    
   // initialize the local indexes to indicate the subarrays
   int first1 = first;    // beginning of first subarray
   int last1  = mid;      // end of first subarray
   int first2 = mid + 1;  // beginning of second subarray
   int last2  = last;     // end of second subarray

   // while both subarrays are not empty, copy the
   // smaller item into the temporary array
   int index = 0;                    

   while ((first1 <= last1) && (first2 <= last2)) 
   {
      if ((*compare) (items[first1], items[first2]) <= 0)  //careful here for stable sorting
      {
         temp[index] = items[first1];
         first1++;
      }
      else 
      {
         temp[index] = items[first2];
         first2++;
      }  

      index++;
   } 

   // finish off the nonempty subarray

   // finish off the first subarray, if necessary
   while (first1 <= last1) 
   {
      temp[index] = items[first1];
      first1++;
      index++;
   }  

   // finish off the second subarray, if necessary
   while (first2 <= last2)
   {
      temp[index] = items[first2];
      first2++;
      index++;
   }  

   // copy the result back into the original array
   for (index = 0; index <= last - first; index++) 
   {
      items[index + first] = temp[index];
   }

   delete[] temp;  
}

template < class T >
T** Sort<T>::quickSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   _quickSort(sorted, 0, num_items - 1, compare);
   return sorted;
}

template < class T >
void Sort<T>::_quickSort(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   int pivotIndex;

   if (first < last)
   {
      // create the partition: S1, Pivot, S2
      pivotIndex = partition(items, first, last, compare);

      // sort regions S1 and S2
      _quickSort(items, first, pivotIndex - 1, compare);
      _quickSort(items, pivotIndex + 1, last, compare);
   }  
}  

template < class T >
int Sort<T>::partition(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   // tempItem is used to swap elements in the array
   T* temp; 

   // place pivot in sort[first]             
   choosePivot(items, first, last);      
   T* pivot = items[first];   // reference pivot

   // initially, everything but pivot is in unknown
   int lastS1 = first;          // index of last item in S1

   // move one item at a time until unknown region is empty

   for (int unknown = first + 1; unknown <= last; unknown++) 
   {
      // move item from unknown to proper region
      if ((*compare)(items[unknown], pivot) < 0)  
      {
         // item from unknown belongs in S1
         lastS1++;
         temp = items[unknown];
         items[unknown] = items[lastS1];
         items[lastS1] = temp;
      } 
      // else item from unknown belongs in S2
   } 

   // place pivot in proper position and mark its location
   temp = items[first];
   items[first] = items[lastS1];
   items[lastS1] = temp;
   return lastS1;
}

template < class T >
void Sort<T>::choosePivot(T** items, int first, int last)
{
   int mid = (first + last)/2;
   T* temp = items[first];

   items[first] = items[mid];
   items[mid] = temp;   //simply swap first and mid to take care of worst case for quicksort
}

template < class T >
T** Sort<T>::insertionBinarySort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   _insertionBinarySort(sorted, num_items, compare);
   return sorted;
}

template < class T >
void Sort<T>::_insertionBinarySort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T* temp;
   int position;

   for (int spot = 1; spot < num_items; spot++)
   {
      temp = items[spot];

      // shift larger values to the right
      position = insertLocation(items, temp, spot - 1, compare);  //binary search to minimize comparisons
      for(int i = spot; i > position; i--)
      {
         items[i] = items[i - 1];
      }
            
      items[position] = temp;
   }
}

template < class T >
int Sort<T>::insertLocation(T** items, T* item, int last, int (*compare) (T* one, T* two))
{
   //based on array indices
   int first = 0;
   int mid = first + (last - first)/2;

   while (first <= last)
   {
      int comp = ((*compare) (item, items[mid]));
      if (comp == 0)
      {
         break;
      }
      else if (comp < 0)
      {
         last = mid - 1;
         mid = first + (last - first)/2;
      }
      else 
      {
         first = mid + 1;
         mid = first + (last - first)/2;
      }
   }

   return mid;
}

template < class T >
int Sort<T>::linearSearch(T** items, int num_items, T* item, int (*compare) (T* one, T* two))
{
   return linearSearch(items, num_items, item, 0, compare);
}

template < class T >
int Sort<T>::linearSearch(T** items, int num_items, T* item, int loc, int (*compare) (T* one, T* two))
{
   //we are using a special return type as the cases below are not exceptional
   if (loc == num_items)  //base case end of array
   {
      return -1;  //item not in array (base case #1)
   }

   int index;
   int comp = (*compare) (item, items[loc]);
   if (comp != 0)
   {
      index = linearSearch(items, num_items, item, loc + 1, compare);
   }
   else
   {
      index = loc;
   }

   return index;
}

template < class T >
int Sort<T>::binarySearch(T** items, int num_items, T* item, int (*compare) (T* one, T* two))
{
   return binarySearch(items, num_items, item, 0, num_items - 1, compare);
}

template < class T >
int Sort<T>::binarySearch(T** items, int num_items, T* item, int first, int last, int (*compare) (T* one, T* two)) 
{
   // reaches the base case much faster
   if (first > last) 
   {
      return -1;      // value not in original array (base case #1)
   } 

   int index;
   int mid = first + (last - first)/2;
   int comp = (*compare) (item, items[mid]);
   if (comp == 0) 
   { 
      index = mid;  // value found at search[mid] (base case #2)
   } 
   else if (comp < 0) 
   {
      //making these method calls is extra overhead that recursion requires
      //as it is easy and readable to write a binary search using a loop, that is the preferred implementation
      index = binarySearch(items, num_items, item, first, mid - 1, compare);
   } 
   else 
   {
      index = binarySearch(items, num_items, item, mid + 1, last, compare);
   } 
  
   return index;  //returns the index up through the chain
}

//operates as a MAX heap
template < class T >
T** Sort<T>::heapSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      sorted[i] = items[i];
   }

   _heapSort(sorted, num_items, compare);
   return sorted;
}

template < class T >
void Sort<T>::_heapSort(T** items, int num_items, int (*compare) (T* one, T* two))
{
   T* swap;

   //make the array into an initial heap
   for (int i = num_items/2 - 1; i >= 0; i--)
   {
      _heapRebuild(items, i, num_items - 1, compare);
   }

   //process the largest item, then rebuild the heap
   //repeat until the array is sorted
   for (int last = num_items - 1; last >= 1; last--)
   {
      swap = items[last];  //pull largest off temp[0] and put on sorted region
      items[last] = items[0];    //last piece of array now moves to top (unsorted size decreases by one)
      items[0] = swap;          
      _heapRebuild(items, 0, last - 1, compare);  //must rebuild O(n*logn)
      //the second to last parameter indicates where the unsorted region ends
      //this value gets smaller with each iteration
   }
}

template < class T >
void Sort<T>::_heapRebuild(T** items, int root, int unsorted_end, int (*compare) (T* one, T* two))
//need to keep track of the boundary between the sorted and unsorted regions (unsorted_end)
{
   bool swap = true;

   int parent = root;
   int child = 2*parent + 1;  // index of parent's left child, if any

   while (child <= unsorted_end && swap)
   {
      swap = false;

      //root is not a leaf, so it has a left child at child
      int right_child = child + 1;  // index of right child, if any

      //if parent has a right child, find smaller child
      //note that using a Heap, FIFO order may not be maintained for items with the same priority
      if (right_child <= unsorted_end)
      {
         if ((*compare) (items[right_child], items[child]) > 0)
         {
            child = right_child;  //index of smaller child
         }
      } 

      //if the parent's value is larger than the
      //value in the smaller child, swap values

      if ((*compare) (items[parent], items[child]) < 0)
      {
         T* swap_item = items[parent];
         items[parent] = items[child];
         items[child] = swap_item;
         swap = true;
      }

      parent = child;
      child = 2*parent + 1; //if out of bounds, we are done
   }

//RECURSIVE VERSION
/*
   // if the root is not a leaf and the root's search key 
   // is less than the larger of the search keys in the
   // root's children
   int child = 2*root + 1;  // index of root's left child, if any

   if (child <= unsorted_end)  // if child <= unsorted_end, root is not a leaf, so it has a left child at child
   {
      int rightChild = child + 1;  // index of right child, if any

      // if root has a right child, find larger child
      if ((rightChild <= unsorted_end) && (*compare) (items[rightChild], items[child]) > 0) 
      {
         child = rightChild;    // index of larger child
      } 

      // if the root's value is smaller than the
      // value in the larger child, swap values
      if ((*compare) (items[root], items[child]) < 0)
      {
         T* temp = items[root];
         items[root] = items[child];
         items[child] = temp;
         // transform the new subtree into a heap
         _heapRebuild(items, child, unsorted_end, compare);
      } 
   }  
   // if root is a leaf, do nothing
*/
} 

#endif

