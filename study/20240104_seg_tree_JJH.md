### [Segment Tree - Range Update]

```cpp
#pragma once

#include <cstdio>

template<int N>
struct SegmentTree {
	int tree[N * 4];

	void init() {
		for (int i = 0; i < N * 4; i++) { tree[i] = 0; }
	}
	void updateRange(int left, int right, int value) {
		updateRange(1, 0, N - 1, left, right, value);
	}
	int queryPoint(int idx) {
		return queryPoint(1, 0, N - 1, idx);
	}
	int queryRange(int left, int right) {
		return queryRange(1, 0, N - 1, left, right);
	}

	// recursive
	int updateRange(int n, int s, int e, int left, int right, int value) {
		if (right < s || e < left) { return 0; }
		if (left <= s && e <= right) { 
			tree[n] += value;
			printf(">> tree[%d] = %d\n", n, tree[n]);
			return tree[n];
		}

		int m = (s + e) / 2;
		int a = updateRange(n * 2, s, m, left, right, value);
		int b = updateRange(n * 2 + 1, m + 1, e, left, right, value);
		return a + b;
	}
	int queryPoint(int n, int s, int e, int idx) {
		int res = 0;
		if (idx < s || e < idx) { return 0; }

		res += tree[n];
		if (s == e) {
			printf(">> tree[%d] = %d\n", n, tree[n]);
			return res;
		}

		int m = (s + e) / 2;
		if (idx <= m) { res += queryPoint(n * 2, s, m, idx); }
		else { res += queryPoint(n * 2 + 1, m + 1, e, idx); }
		return res;
	}
	int queryRange(int n, int s, int e, int left, int right) {
		int res = 0;
		if (right < s || e < left) { return 0; }
		if (left <= s && e <= right) {
			printf(">> tree[%d] = %d\n", n, tree[n]);
			return res += tree[n];	// res += tree[n].base * tree[n].count
		}

		int m = (s + e) / 2;
		int a = queryRange(n * 2, s, m, left, right);
		int b = queryRange(n * 2 + 1, m + 1, e, left, right);
		return res += a + b;
	}
};
```

### [test_seg_tree.cpp]

```cpp
#include "seg_tree.h"
#include <cstdio>

const int N = 8;
SegmentTree<N> seg;

int main()
{
    seg.init();
    seg.updateRange(0, 6, 1);

    // point query
    printf("\n*** Point Query ***\n");
    //printf(">> [%d] = %d\n", 0, seg.queryPoint(0));
    //printf(">> [%d] = %d\n", 1, seg.queryPoint(1));
    //printf(">> [%d] = %d\n", 2, seg.queryPoint(2));
    //printf(">> [%d] = %d\n", 3, seg.queryPoint(3));
    //printf(">> [%d] = %d\n", 4, seg.queryPoint(4));
    //printf(">> [%d] = %d\n", 5, seg.queryPoint(5));

    printf("\n*** Range Query ***\n");
    printf(">> Sum [1, 4] = %d\n", seg.queryRange(1, 4));


    return 0;
}
```

### [Segment Tree] Lazy Propagation

```cpp
#include <map>
#include <string>

using namespace std;

const int MAX = 1'000'000;

struct SegmentTree
{
	int tree[(MAX + 1) * 4 + 1];
	int lazy[(MAX + 1) * 4 + 1];

	void init() {
		for (int i = 0; i < (MAX + 1) * 4 + 1; i++)
			lazy[i] = tree[i] = 0;
	}

	void propagate(int n, int s, int e)
	{
		if (lazy[n] == 0)
			return;

		int sum = lazy[n] * (e - s + 1);
		tree[n] += sum;

		if (s != e)
		{
			lazy[n * 2] += lazy[n];
			lazy[n * 2 + 1] += lazy[n];
		}

		lazy[n] = 0;
	}

	void update(int n, int s, int e, int left, int right)
	{
		propagate(n, s, e);

		/* s e left rigth s e */

		if (e < left || right < s)
			return;

		if (left <= s && e <= right)
		{
			lazy[n] += 1;
			propagate(n, s, e);
			return;
		}

		int m = (s + e) / 2;
		update(n * 2, s, m, left, right);
		update(n * 2 + 1, m + 1, e, left, right);

		tree[n] = tree[n * 2] + tree[n * 2 + 1];
	}

	int query(int n, int s, int e, int left, int right)
	{
		propagate(n, s, e);

		if (e < left || right < s)
			return 0;

		if (left <= s && e <= right)
		{
			return tree[n];
		}

		int m = (s + e) / 2;
		return query(n * 2, s, m, left, right)
			+query(n * 2 + 1, m + 1, e, left, right);
	}
}segtree;

int id;
map<string, int> index;
int parent[MAX];
int dist[MAX];

void init(char mAncestor[], int mLastday)
{
	index.clear();
	
	id = 1;
	index[string(mAncestor)] = id++;

	segtree.init();
	segtree.update(1, 0, MAX, 0, mLastday);
}


int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
	int cid = id;
	index[string(mName)] = id++;

	int pid = index.find(string(mParent))->second;
	parent[cid] = pid;
	dist[cid] = dist[pid] + 1;

	segtree.update(1, 0, MAX, mFirstday, mLastday);

	return dist[cid];
}


int distance(char mName1[], char mName2[])
{
	int a = index.find(string(mName1))->second;
	int b = index.find(string(mName2))->second;

	if (dist[a] > dist[b])
		swap(a, b);

	int ret = 0;

	while (dist[a] != dist[b])
	{
		ret++;
		b = parent[b];
	}

	if (a == b)
		return ret;

	while (parent[a] != parent[b])
	{
		b = parent[b], a = parent[a];
		ret += 2;
	}

	ret += 2;
	return ret;
}

int count(int mDay)
{
	int ret = segtree.query(1, 0, MAX, mDay, mDay);
	return ret;
}
```
