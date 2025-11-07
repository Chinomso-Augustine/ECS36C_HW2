// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"

int numComparisonsQuicksort; // Declaring the integer numComparisons variable for counting and incrementation
int numMemAccessesQuicksort; // Declaring the integer numMemory Accessesvariable for counting and incrementation

void QuickSort(std::vector<int>* numbers) { // Calling the Quick sort function declared in the quicksort header file.
   QuickSortRecurse(numbers, 0, numbers->size() - 1);
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k) { // Calling the other quicksort function declared in the quicksort header file.
   int j = 0; // initializing j to be 0
   numComparisonsQuicksort++; // for base case check

   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }

   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k);

   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j);
   QuickSortRecurse(numbers, j + 1, k);
}

int Partition(std::vector<int>* numbers, int i, int k) { // Defining a function name Partition 
   int l = i; // setting the integer l to i probably left pointer
   int h = k; // setting the integer h to k
   int midpoint = i + (k - i) / 2; // finding the middle index of i and k
   int pivot = (*numbers)[midpoint]; // gets the pivot value from the vector
   int temp; // declares a temporary variable
   bool done = false; // controls the main partition loop

   numMemAccessesQuicksort++; //incrementing the count for number of memory accesses by 1

   while (!done) {
      numComparisonsQuicksort++; // while check incrementation

      // Increment l while numbers[l] < pivot
      while ((*numbers)[l] < pivot) {
         numComparisonsQuicksort++;    // comparison incrementation by 1
         numMemAccessesQuicksort += 2; // Once comparison is done, memory access incrementation by 2
         ++l; // L is incremented by 1 before it is even altered
      }

      // Decrement h while pivot < numbers[h]
      while (pivot < (*numbers)[h]) {
         numComparisonsQuicksort++;    // increments the comparison quicksort count by 1
         numMemAccessesQuicksort += 2; // increments the memory access count by 2
         --h;
      }
      numComparisonsQuicksort++; // increment comparison for l >= h
      if (l >= h) { // checking if l is greater than or equal to h
         done = true;
      } else {
         // Swap numbers[l] and numbers[h]
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;
         ++l; // increments the left pointer before alteration
         --h; // decrements h before alteration
      }
   }
   return h;
}
