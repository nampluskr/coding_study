### [Hash Table] 임형우

```cpp
#if 1
#define MAX_DATA    20
#define MAX_TABLE   10

struct Value {
    int key;
    int next;
};

Value values[MAX_DATA];
int value;
int table[MAX_TABLE];

int hashfunc(int key) {
    return key & (MAX_TABLE - 1);
    //return key % MAX_TABLE;
}

void clear() {
    value = 0;
    for (int i = 0; i < MAX_TABLE; i++)
        table[i] = 0;
}

void emplace(int key, int value) {
    int hash_value = hashfunc(key);
    values[value].key = key;
    values[value].next = table[hash_value];
    table[hash_value] = value;
}

int find(int key) {
    int hash_value = hashfunc(key);
    int next = table[hash_value];

    while (next && key != values[next].key)
        next = values[next].next;
    return next;
}

int main()
{
    clear();

    emplace(11, 0);
    emplace(12, 1);
    emplace(13, 2);

    emplace(21, 3);
    emplace(22, 4);
    emplace(23, 5);

    emplace(31, 6);
    emplace(32, 7);
    emplace(33, 8);

    int idx;
    idx = find(11);
    idx = find(21);
    idx = find(31);
    idx = find(41);

    return 0;
}
#endif
```

### [Hash Table] 데이터 입력시

```cpp
#if 1
#define MAX_DATA    20
#define MAX_TABLE   10

struct Data {
    int index;      // table
    int ID;
    int number;
};

Data data[MAX_DATA];
int data_index;
int table[MAX_TABLE];

int hashfunc(int ID) {
    return ID% MAX_TABLE;
}


void init() {
    data_index = 0;
    for (int i = 0; i < MAX_TABLE; i++)
        table[i] = 0;
}

void insert(int ID, int number) {
    int hashValue = hashfunc(ID);
    data[data_index].ID = ID;
    data[data_index].index = table[hashValue];
    data[data_index].number = number;
    table[hashValue] = data_index;
    data_index++;
}

int find(int ID) {
    int hashValue = hashfunc(ID);
    int next_index = table[hashValue];

    while (next_index && ID != data[next_index].ID)
        next_index = data[next_index].index;
    return next_index;
}


int main()
{
    init();

    insert(11, 10);
    insert(12, 20);
    insert(13, 30);

    insert(21, 40);
    insert(22, 50);
    insert(23, 60);

    insert(31, 70);
    insert(32, 80);
    insert(33, 90);

    int idx;
    idx = find(11);
    idx = find(21);
    idx = find(31);

    return 0;
}
#endif
```
