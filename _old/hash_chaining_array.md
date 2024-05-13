### Hash Chaining using Array

```cpp
#include <cstdio>

#define MAX_DATA    20
#define MAX_TABLE   2

struct Data {
    int key, prev;      // hash chaining
};
Data db[MAX_DATA];
int cnt;

int hash_func(int key) { return key % MAX_TABLE; }

struct HashMap {
    int table[MAX_TABLE];
    Data* db = ::db;    // global Data db[MAX_DATA]
    int& cnt = ::cnt;   // global int cnt

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i] = -1;
    }
    void insert(int key, int idx) {
        int hash_value = hash_func(key);
        db[idx].key = key;
        db[idx].prev = table[hash_value];
        table[hash_value] = idx;
    }
    int find(int key) {
        int hash_value = hash_func(key);
        int cur = table[hash_value];
        while (cur != -1 && key != db[cur].key)
            cur = db[cur].prev;
        return cur;
    }
    void erase(int key) {
        int idx = find(key);
        if (idx!= -1)
            db[idx].key = -1;
    }
    int operator[](int key) {
        int idx = find(key);
        if (idx == -1) {
            insert(key, cnt);
            return cnt++;
        }
        return idx;
    }
};

HashMap map;

Data& get_data(int key) {
    return db[map[key]];
}


int main()
{
    cnt = 0;
    map.clear();

    printf("\n=== insert ===\n");
    map.insert(1001, cnt++);
    map.insert(1002, cnt++);
    map.insert(1003, cnt++);
    map.insert(1004, cnt++);
    map.insert(1005, cnt++);
    map.insert(1006, cnt++);

    printf("map[%d] = %d\n", 1001, map.find(1001));
    printf("map[%d] = %d\n", 1002, map.find(1002));
    printf("map[%d] = %d\n", 1003, map.find(1003));
    printf("map[%d] = %d\n", 1004, map.find(1004));
    printf("map[%d] = %d\n", 1005, map.find(1005));
    printf("map[%d] = %d\n", 1006, map.find(1006));

    printf("\n=== operator[] ===\n");
    printf("map[%d] = %d\n", 1001, map[1001]);
    printf("map[%d] = %d\n", 1002, map[1002]);
    printf("map[%d] = %d\n", 1003, map[1003]);
    printf("map[%d] = %d\n", 1004, map[1004]);
    printf("map[%d] = %d\n", 1005, map[1005]);
    printf("map[%d] = %d\n", 1006, map[1006]);

    printf("\n=== erase ===\n");
    map.erase(1001);
    map.erase(1002);
    map.erase(1003);
    map.erase(1004);

    printf("map[%d] = %d\n", 1001, map.find(1001));
    printf("map[%d] = %d\n", 1002, map.find(1002));
    printf("map[%d] = %d\n", 1003, map.find(1003));
    printf("map[%d] = %d\n", 1004, map.find(1004));
    printf("map[%d] = %d\n", 1005, map.find(1005));
    printf("map[%d] = %d\n", 1006, map.find(1006));

    printf("\n=== clear ===\n");
    map.clear();

    printf("map[%d] = %d\n", 1001, map.find(1001));
    printf("map[%d] = %d\n", 1002, map.find(1002));
    printf("map[%d] = %d\n", 1003, map.find(1003));
    printf("map[%d] = %d\n", 1004, map.find(1004));
    printf("map[%d] = %d\n", 1005, map.find(1005));
    printf("map[%d] = %d\n", 1006, map.find(1006));

    return 0;
}
```
