// Quicksort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"

int numComparisonsQuicksort = 0; //numComparsionQuicksort global variable 
int numMemAccessesQuicksort = 0; //numMemQuicksort global variable 

void QuickSort(std::vector<int> *numbers)
{
   QuickSortRecurse(numbers, 0, numbers->size() - 1);
}

void QuickSortRecurse(std::vector<int> *numbers, int i, int k)
{
   int j = 0;
   // numComparisonsQuick++; // for base case check

   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k)
   {
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

int Partition(std::vector<int> *numbers, int i, int k)
{
   int l = i;
   int h = k;
   int midpoint = i + (k - i) / 2;
   int pivot = (*numbers)[midpoint];
   int temp;
   bool done = false;

   numMemAccessesQuicksort++; // increment by 1

   while (!done)
   {

      // Increment l while numbers[l] < pivot
      while ((*numbers)[l] < pivot)
      {
         numComparisonsQuicksort++;    // comparison incremented by 1
         numMemAccessesQuicksort += 2; //numAccessQuickSort incremented by 2
         ++l;
      }
      numComparisonsQuicksort++; //comparison incremented by 1

      // Decrement h while pivot < numbers[h]
      while (pivot < (*numbers)[h])
      {
         numComparisonsQuicksort++;    // comparison incremented by 1
         numMemAccessesQuicksort += 2; // incremented by 2
         --h;
      }
      numComparisonsQuicksort++; //increment by 1
      if (l >= h)
      {
         numMemAccessesQuicksort += 2; //increment by 2

         done = true;
      }
      else
      {
         // Swap numbers[l] and numbers[h]
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;
         numMemAccessesQuicksort += 6; //increment by 6
         ++l;
         --h;
      }
   }
   return h;
}
