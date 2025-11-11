// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void InsertionSort(std::vector<int>* numbers);

// shared global counters
extern int numComparisonsInsertion;
extern int numMemAccessesInsertion;