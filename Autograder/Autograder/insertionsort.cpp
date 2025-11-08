// Insertion Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
int numComparisonsInsertion = 0; // global variable to count number of comparisons made
int numMemAccessesInsertion = 0; // global variable to count number of memory accesses made

void InsertionSort(std::vector<int> *numbers)
{
   int i = 0;    // Original code
   int j = 0;    // Original code
   int temp = 0; // Temporary variable for swap

   for (i = 1; i < numbers->size(); ++i)
   {
      numComparisonsInsertion++; // increments numComparisonInsertion by 1

      j = i; //set j to current index
      numMemAccessesInsertion++; // increment numAccessInsertion by 1

      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1])
      {
         numComparisonsInsertion++;    // Incrementing the number of comparisons by 1
         numMemAccessesInsertion += 4; // Incrementing the number of memory access by 4

         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
         --j;
      }
      numComparisonsInsertion++; //increment numComparisonInsertin by 1
   }
}