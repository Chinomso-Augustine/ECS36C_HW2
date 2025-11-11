// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
 int numComparisonsInsertion;
 int numMemAccessesInsertion;

void InsertionSort(std::vector<int>* numbers) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap

   for (i = 1; i < numbers->size(); ++i) {
      
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         numComparisonsInsertion++; // Incrementing the number of comparisons by 1
         numMemAccessesInsertion+=2; // Incrementing the number of memory access by 2
         
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
        numMemAccessesInsertion+=4; // Incrementing the number of memory accesses by 4
         --j;
      }
      numComparisonsInsertion+=1;
   }   
   return;
}