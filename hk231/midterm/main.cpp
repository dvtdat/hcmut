#include <bits/stdc++.h>

using namespace std;
/*
Question: What will be the result of foo(4, 7)?
Answer: foo(4, 7) = 120
*/
int foo(int x, int y) {
    if (x > y) return - 1;
    if (x == y) return 1;
    return x * foo(x + 1, y);
}

/*
Question: What will be the result of soo(8)?
Answer: soo(8) = 156
*/
int soo(int n) {
    if (n <= 0) return 0;
    if (n % 2 == 0) return soo(n - 1) + soo(n - 2) + n;
    return 2 * soo(n - 1) + 1;
}

/*
Question: What will be the time complexity of coo(n)?
Answer: O(sqrt(n))
*/
void coo(int n) {
    int i = 0, s = 0;
    while (s < n) {
        i++;
        s += i;
    }
}


/*
Question: Given Merge Sort in a worst case scenario will take 30 second to sort
an array with 64 element. What will be the size of the array if the algorithm
take 06 minutes to finish sorting?
Answer:
    - O(1) = 30 / O(NlogN) = 360 / O(XlogX)
    - With N = 64, solve for X
    - X = 512
*/

/*
Question: Given A = [37, 27, 43, 3, 9, 82, 10], using Selection Sort what 
will be the total cost of sorting if a comparision take 06 USD, and a swap 
take 12 USD?
Answer: 198
*/

/*
Question: Given A = [37, 27, 43, 3, 9, 82, 10], using Shell Sort with K = 3,
after sorting Segment 01 (first segment will be indexed 00), what will the
array become?
Answer:
*/

/*
Question: Given A = [52, 25, 76, 67, 89], reorder A so that the number of comparision
when using Quick Sort will be maximum if we choose the first element of that array
to be the pivot.
Answer:
*/



int main() {

}