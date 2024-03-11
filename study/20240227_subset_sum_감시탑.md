### [Subset Sum] 1Sum / 2Sum / 3Sum Two Pointers

```cpp
#include <vector>
#include <algorithm>
using namespace std;

//int n = 12;
vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
int n = arr.size();
vector<vector<int>> sol;
vector<int> bits;
int cnt;


void select1(const vector<int>& arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        cnt++;
        if (arr[i] == target) {
            sol.push_back({ arr[i] });
            bits.push_back((1 << i));
        }
        else if (target < arr[i])
            return;
    }
}
void select2(const vector<int>& arr, int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        cnt++;
        int sum = arr[lo] + arr[hi];
        if (sum == target) {
            sol.push_back({ arr[lo], arr[hi] });
            bits.push_back((1 << lo) | (1 << hi) );
            lo++; hi--;
        }
        else if (sum < target) lo++;
        else hi--;
    }
}
void select3(const vector<int>& arr, int n, int target) {
    for (int i = 0; i < n - 2; i++) {
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            cnt++;
            int sum = arr[i] + arr[lo] + arr[hi];
            if (sum == target) {
                sol.push_back({ arr[i], arr[lo], arr[hi] });
                bits.push_back((1 << i) | (1 << lo) | (1 << hi));
                lo++; hi--;
            }
            else if (sum < target) lo++;
            else hi--;
        }
    }
}


int main()
{
    int target = 12;
    sol.clear();

    cnt = 0;
    sort(arr.begin(), arr.end());
    select1(arr, n, target);    // O(n)
    select2(arr, n, target);    // O(n)
    select3(arr, n, target);    // O(n^2)

    return 0;
}
```

### [Subset Sum] Backtracking

```cpp
#include <vector>
using namespace std;

#define INF 0x7ffffff

int n = 12;
vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
//vector<int> arr = { 1, 2, 3, 4, 5 };
vector<int> selected;
vector<vector<int>> sol;
int cnt;

void show(const vector<int>& arr, int cnt, int k) {
    printf("[%2d] k=%d: [ ", cnt, k);
    for (int x : arr)
        printf("%d, ", x);
    printf("]\n");
}

void show(const vector<int>& arr, int cnt, int k, int sum, int max, int size) {
    printf("[%2d] k=%d, sum=%2d, max=%2d, size=%d: [ ", cnt, k, sum, max, size);
    for (int x : arr)
        printf("%d, ", x);
    printf("]\n");
}

// combination
void comb(int k) {
    show(selected, ++cnt, k);

    for (int i = k; i < arr.size(); i++) {
        selected.push_back(arr[i]);
        comb(i + 1);
        selected.pop_back();
    }
}

inline int max(int a, int b) { return (a < b) ? b : a; }
inline int min(int a, int b) { return (a < b) ? a : b; }
int res;
int target;

void dfs(int k, int sum, int maxVal, int size) {
    cnt++;

    if (sum == target) {
        res = min(res, maxVal);
        printf(">> Current solution = %d\n", res);
        show(selected, cnt, k, sum, maxVal, size);
        sol.push_back(selected);
        return;
    }

    for (int i = k; i < arr.size(); i++) {
        if (sum + arr[i] <= target && size < 3) {
            selected.push_back(arr[i]);  // indices
            dfs(i + 1, sum + arr[i], max(maxVal, arr[i]), size + 1);
            selected.pop_back();    // backtrack
        }
    }
}

int main()
{
    cnt = 0;
    res = INF;
    target = 12;
    selected.clear();

    //comb(0);
    dfs(0, 0, 0, 0);


    return 0;
}
```

### [subset sum] disjoint merge

```cpp
#include <vector>
using namespace std;

#define INF 0x7fffffff

vector<int> arr = { 1, 2, 3, 4, 5, 6 };
int n = arr.size();
int target = 6;

vector<vector<int>> sol;
vector<int> selected;
vector<int> bits;
vector<int> subset;

void show(const vector<int>& arr) {
    printf("[ ");
    for (int x : arr)
        printf("%d, ", x);
    printf("]\n");
}

void get_subset(int bit, int n) {
    for (int i = 0; i < n; i++)
        if (bit & (1 << i))
            subset.push_back(arr[i]);
}

// arr -> bits
void solve(int k, int sum, int bit) {
    if (sum == target) {
        show(selected);
        sol.push_back(selected);
        bits.push_back(bit);
        return;
    }
    for (int i = k; i < n; i++)
        if (sum + arr[i] <= target) {
            selected.push_back(arr[i]);
            solve(i + 1, sum + arr[i], bit | (1 << i));
            selected.pop_back();
        }
}

// bits -> disjoint
void merge(int k, int cnt, int bit) {
    if (k == n - 2 && cnt > 1) {
        subset.clear();
        for (int i = 0; i < n; i++)
            if (bit & (1 << i))
                subset.push_back(arr[i]);
        show(subset);
        return;
    }
    for (int i = k; i < bits.size(); i++)
        if ((bit & bits[i]) == 0) {
            selected.push_back(bits[i]);
            merge(i + 1, cnt + 1, bit | bits[i]);
            selected.pop_back();
        }
}


int getMaxValue(int bit) {
    int i;
    bit /= 2;
    for (i = 0; bit != 0; i++) bit /= 2;
    return arr[i];
}

int getSol(const vector<int>& s) {
    if (s.empty()) return -1;
    int res = INF;
    for (int bit : s)
        res = min(res, getMaxValue(bit));
    return -1;
}


int main()
{
    printf(">> Solve subset sum:\n");
    selected.clear();
    solve(0, 0, 0);

    printf(">> Select disjoint subsets:\n");
    selected.clear();
    merge(0, 0, 0);

    return 0;
}
```

### [감시탑] 상품권 배분

```cppp
#include <vector>
#include <unordered_map>
using namespace std;

#define MAX_NODES   (17000 + 1000)  // add() 함수의 호출 횟수는 17,000 이하이다.
#define MAX_GROUPS  1000            // N: 그룹의 개수 ( 3 ≤ N ≤ 1,000 )
#define REMOVED     1

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

struct Node {
    int totalNum;
    int parent;

    int numChildren;
    vector<int> childList;
    int state;
};
Node nodes[MAX_NODES];
int nodeCnt;
unordered_map<int, int> nodeMap;

int groups[MAX_GROUPS];
int groupCnt;

//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(int mId) {
    int nIdx;
    auto iter = nodeMap.find(mId);
    if (iter == nodeMap.end()) {
        nIdx = nodeCnt++;
        nodeMap.emplace(mId, nIdx);
    }
    else { nIdx = iter->second; }
    return nIdx;
}

void update_parent(int cur, int mNum) {
    int parent = nodes[cur].parent;
    while (parent != -1) {
        nodes[parent].totalNum += mNum;
        parent = nodes[parent].parent;
    }
}

void remove_children(int cur) {
    nodes[cur].state = REMOVED;
    for (int child : nodes[cur].childList)
        remove_children(child);
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mId[], int mNum[])
{
    for (int i = 0; i < MAX_NODES; i++) nodes[i] = {};
    nodeCnt = 0;
    nodeMap.clear();

    for (int i = 0; i < N; i++) {
        int nIdx = get_nodeIndex(mId[i]);
        nodes[nIdx].totalNum = mNum[i];
        nodes[nIdx].parent = -1;
    }
    groupCnt = N;
}

// 17,000
int add(int mId, int mNum, int mParent)
{
    int res = -1;
    int pIdx = get_nodeIndex(mParent);

    if (nodes[pIdx].numChildren < 3) {
        int nIdx = get_nodeIndex(mId);
        nodes[pIdx].numChildren++;
        nodes[pIdx].childList.push_back(nIdx);

        nodes[nIdx].totalNum = mNum;
        nodes[nIdx].parent = pIdx;
        update_parent(nIdx, mNum);
        res = nodes[pIdx].totalNum;
    }
    return res;
}

// 2,000
int remove(int mId)
{
    int res = -1;
    int nIdx = get_nodeIndex(mId);

    if (nodes[nIdx].state != REMOVED) {
        int pIdx = nodes[nIdx].parent;
        int mNum = nodes[nIdx].totalNum;
        nodes[pIdx].numChildren--;
        update_parent(nIdx, -mNum);
        remove_children(nIdx);
        res = mNum;
    }
    return res;
}

// 상품권 개수 (상한치) x 주어졌을 때, 합이 K 보다 작거나 같은가?
bool isValid(int x, int K) {
    int sum = 0;
    for (int i = 0; i < groupCnt; i++)
        sum += min(x, groups[i]);
    return sum <= K;
}

// 1,000
int distribute(int K)
{
    int res = 0;
    int start = 0;
    int end = 0;
    for (int i = 0; i < groupCnt; i++) {
        groups[i] = nodes[i].totalNum;
        end = max(end, groups[i]);
    }
    // parametric search
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (isValid(mid, K)) {
            res = mid;
            start = mid + 1;
        }
        else
            end = mid - 1;
    }
    return res;
}
```
