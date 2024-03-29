#include <iostream>
#include <bitset>
using namespace std;

// Maximum allowed query value 
# define MAXSUM 10000 

// function to check whether a subset sum equal to n 
// exists in the array or not. 
void processQueries(int query[], int nq, bitset<MAXSUM> bit)
{
    // One by one process subset sum queries 
    for (int i = 0; i < nq; i++)
    {
        int x = query[i];

        // If x is beyond size of bit[] 
        if (x >= MAXSUM)
        {
            cout << "NA, ";
            continue;
        }

        // Else if x is a subset sum, then x'th bit 
        // must be set 
        bit[x] ? cout << "Yes, " : cout << "No, ";
    }
}

// function to store all the subset sums in bit vector 
void preprocess(bitset<MAXSUM>& bit, int arr[], int n)
{
    // set all the bits to 0 
    bit.reset();

    // set the 0th bit because subset sum of 0 exists 
    bit[0] = 1;

    // Process all array elements one by one 
    for (int i = 0; i < n; ++i)

        // Do OR of following two 
        // 1) All previous sums. We keep previous value 
        // of bit. 
        // 2) arr[i] added to every previous sum. We 
        // move all previous indexes arr[i] ahead. 
        bit |= (bit << arr[i]);
}

// Driver program 
int main()
{
    int arr[] = { 3, 1, 5 };
    int query[] = { 8, 7 };

    int n = sizeof(arr) / sizeof(arr[0]);
    int nq = sizeof(query) / sizeof(query[0]);

    // a vector of MAXSUM number of bits 
    bitset<MAXSUM> bit;

    preprocess(bit, arr, n);
    processQueries(query, nq, bit);

    return 0;
}