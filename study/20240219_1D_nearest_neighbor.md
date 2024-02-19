### 1D 가장 가까운 점 구하기 (BST, 이진 탐색)

```cpp
#include <vector>
#include <set>
using namespace std;

set<int> s = { 3, 10, 1 };
//set<int> s = {};

int lower(const set<int>& s, int x) {
    auto iter = s.lower_bound(x);
    return (iter == s.begin()) ? -1 : *(--iter);
}

int upper(const set<int>& s, int x) {
    auto iter = s.lower_bound(x);
    return (iter == s.end()) ? -1 : *iter;
}

int nearest(int x) {
    int low = lower(s, x);
    int high = upper(s, x);

    if (low == -1 && high == -1)
        return -1;
    else if (low == -1)
        return high;
    else if (high == -1)
        return low;
    else if (x - low < high - x)
        return low;
    else if (x - low > high - x)
        return high;
    else // x - low == high - x
        return low;
}


int main()
{
    int x;

    x = 0;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 1;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 2;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 3;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 5;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));
    
    x = 7;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 9;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    x = 11;
    printf(">> x = %d: [%2d, %2d] >> nearset = %d\n", x, lower(s, x), upper(s, x), nearest(x));

    return 0;
}
```
