#include <bits/stdc++.h>

using namespace std;

/*
    SOME IMPORTANT FACT THAT YOU MUST REMEMBER
*/

/* SHELL SORT

*/

/* MERGE SORT
    - Compulsory helper function: merge()
    - Merge Sort perform well with singly linked list, as merging doesn't require random access to list element.
    - Merging: O(i) with i is the total length of the two subarrays.
    - There are logN levels of recursion.
    - There should be N total steps of merging.
    - The complexity of O(NlogN) should be consistent for all cases
    - Average case (represent with recurrence relation):
        T(n) = 2 * T(n / 2) + cn
        T(1) = c
*/

/* QUICK SORT
    - 02 compulsory helper function: findpivot() and partition()
    - Best way of finding a pivot should be randomizing it, but it will be expensive, therefore, it is better to use the middle position in the array
    - Worst case scenario O(N^2) will occur when pivot is poorly choose. If it is choosen randomly, this will not be the case.
    - Best case scenario O(NlogN) will occur when findpivot() always break the array into two equal halves. => logN levels of partitions
    - Average case:
        T(n) = cn + (1 / n) * sum(T(k) + T(n - 1 - k))(k = 0 -> n - 1)
        T(0) = T(1) = c

    - When the array is divided into subarrays with such small sizes and be "nearly" sorted, it is better to switch  and take advantage of best-case performance of Insertion Sort.
*/

/* HEAP SORT
    - Praticality of using BST for sorting
    - Disadvantages: using more spaces, chances of unbalanced tree (O(n^2)),...
    - Compulsory helper function: buildheap()
*/

/* Comparison of Sorting Algorithms
    - For extremely large arrays, Insertion Sort is the best of internal sorting algorithms.
    - Quicksort is overall the best algorithms, except for array size <= 10.
*/


int main() {
    
}