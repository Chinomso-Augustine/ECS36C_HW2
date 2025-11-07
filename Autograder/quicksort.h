// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector> // Used for the vector data structure

// All of these are functions used to call the quicksrot algorithm on our json file data 
void QuickSort(std::vector<int>* numbers);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k);
int Partition(std::vector<int>* numbers, int i, int k);