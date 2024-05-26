#include <cstdio>

#define MAX_DATA    20
#define MAX_TABLE   17

struct Data {
    int number;
    int key, next;      // for hash
};

Data db[MAX_DATA];
int idx;

int hash_func(int key) { return key % MAX_TABLE; }

struct HashMap {
    int table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) table[i] = 0;
        for (int i = 0; i < MAX_DATA; i++) { db[i].key = -1, db[i].next = 0; }
    }
    void insert(int key, int value) {
        int hash_value = hash_func(key);
        db[value].key = key;
        db[value].next = table[hash_value];
        table[hash_value] = value;
    }
    int find(int key) {
        int hash_value = hash_func(key);
        int next = table[hash_value];

        while (next && key != db[next].key)
            next = db[next].next;
        return next;
    }
    Data& operator[](int key) {
        int dataIdx = find(key);
        if (dataIdx == 0) {
            insert(key, idx);
            dataIdx = idx++;
        }
        return db[dataIdx];
    }
    void erase(int key) {
        int idx = find(key);
    }
};

HashMap map;


int main()
{
    idx = 1;
    map.clear();

    db[idx].number = 10; map.insert(1111, idx++);
    db[idx].number = 20; map.insert(2222, idx++);
    db[idx].number = 30; map.insert(3333, idx++);

    printf("\n=== find ===\n");
    printf("map[%d] = %d\n", 1111, map.find(1111));
    printf("map[%d] = %d\n", 2222, map.find(2222));
    printf("map[%d] = %d\n", 3333, map.find(3333));
    printf("map[%d] = %d\n", 4444, map.find(4444));
    printf("map[%d] = %d\n", 5555, map.find(5555));

    printf("\n=== operator[] ===\n");
    printf("map[%d].number = %d\n", 1111, map[1111].number);
    printf("map[%d].number = %d\n", 2222, map[2222].number);
    printf("map[%d].number = %d\n", 3333, map[3333].number);
    printf("map[%d].number = %d\n", 4444, map[4444].number);
    printf("map[%d].number = %d\n", 5555, map[5555].number);


    return 0;
}