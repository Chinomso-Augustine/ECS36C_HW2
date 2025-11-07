// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
 int numComparisonsInsertion; // Declaring the integer numComparisons variable for counting and incrementation
 int numMemAccessesInsertion; // Declaring the integer numMemory Accessesvariable for counting and incrementation

void InsertionSort(std::vector<int>* numbers) {
   int i = 0; // Setting I to 0 initializing it.
   int j = 0; // Setting j to 0 initializing it
   int temp = 0;  // Temporary variable for swap

   for (i = 1; i < numbers->size(); ++i) { // going through the entire list of numbers and the size of that array
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         numComparisonsInsertion++; // Incrementing the number of comparisons by 2
         numMemAccessesInsertion+=4; // Incrementing the number of memory access by 2
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
   
         --j; // Decrements j before the change
      }
      numComparisonsInsertion++; // Increments the umber of comparisons by 1
   }
   return;
}