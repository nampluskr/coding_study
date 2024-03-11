#if 0
// subset sum problem: k-sum
// https://www.geeksforgeeks.org/cpp-bitset-and-its-application

#include <bitset>
#include <vector>
using namespace std;

#define MAX_SIZE    10


bitset<MAX_SIZE> bit;
vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int n = arr.size();
int k = 6;

// set(), reset(), filip(), count()
// test(), any(), none(), all(), size()

void show(const bitset<MAX_SIZE>& bit) {
    printf("%s\n", bit.to_string().c_str());
}

void ksum(int idx, int sum, int cnt, bitset<MAX_SIZE> bit) {
    if (sum == k) {
        return;
    }
    
    for (int i = idx; i < n; i++)
        ksum(i + 1, sum + arr[i], cnt + 1, bit | );
}


int main()
{
    


    return 0;
}
#endif