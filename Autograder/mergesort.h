// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector> // Used for creating vector arrays and data structure

// All of these are functon declarations for the Merge sort function to run on the files we are looking at
void MergeSort(std::vector<int>* numbers);
void MergeSortRecurse(std::vector<int>* numbers, int i, int k);
void Merge(std::vector<int>* numbers, int i, int j, int k);
