// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

int numComparisonsMergesort; // Declaring the integer numComparisons variable for counting and incrementation
int numMemAccessesMergesort; // Declaring the integer numMemory Accessesvariable for counting and incrementation

void MergeSort(std::vector<int>* numbers) { // Calling the Mergesort function declared in the mergesort header file.
   MergeSortRecurse(numbers, 0, numbers->size() - 1);
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k) { // Calling the other Mergesort function declared in the mergesort header file.
   int j = 0; // Initializing j to be 0
   numComparisonsMergesort++; // Incrementing the count for the number of comparisons for mergesort by 1
   if (i < k) { // Checking if i is less than k
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j);
      MergeSortRecurse(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      numComparisonsMergesort++; // Incrementing the number of comparisons by 1
      numMemAccessesMergesort+=2; // Increasing the number of memoryaccesses by 1
      
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         numMemAccessesMergesort+=2; // Increasing the number of memoryaccesses by 2
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;
      }
      else {
         numMemAccessesMergesort += 2; // Increasing the number of memoryaccesses by 2
         mergedNumbers[mergePos] = (*numbers)[rightPos]; // Copying half of remaining elements from an array into a merged array into the right position
         ++rightPos; // Incrementing the right postion
         
      }
      ++mergePos; // Increments the merge position by 1
   }
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      numMemAccessesMergesort+=2; // condition check
      mergedNumbers[mergePos] = (*numbers)[leftPos]; // Copying half of remaining elements from an array into a merged array in the left position
      ++leftPos; // incrementing the left position by 1
      ++mergePos; // incrementing the merge position by 1
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      numMemAccessesMergesort+=2; // Increasing the number of memoryaccesses by 2
      mergedNumbers[mergePos] = (*numbers)[rightPos]; // Copying half of remaining elements from an array into a merged array in the left position
      ++rightPos; // incrementing the right position by 1
      ++mergePos; // Incrementing the merge position by 1
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numMemAccessesMergesort+=2; // Increasing the number of memoryaccesses by 2
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      
   }
   numComparisonsMergesort++; // incrementing the number of comparisons for merge sort by 1
}
