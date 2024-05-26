#if 0
#define MAX_DATA    20
#define MAX_TABLE   10

struct Data {
    int key;
    int next;
};

Data user_data[MAX_DATA];
int cnt_data;


Data& get_data(int key) {
    int dataIdx;
    int ret = map.find(key);
    if (ret == 0) {
        dataIdx = cnt_data++;
        map.emplace(key, dataIdx);
        return user_data[dataIdx];
    }
    return user_data[ret];
}

int hash(int key) {
    return key & (MAX_TABLE - 1);
    //return key % MAX_TABLE;
}

struct HashMap {
    int table[MAX_TABLE];           // hash table
    Data* database = user_data;     // global user db array
    int& cnt = ::cnt_data;

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i] = 0;
    }

    void emplace(int key, int value) {
        int hash_value = hash(key);
        database[value].key = key;
        database[value].next = table[hash_value];
        table[hash_value] = value;
    }

    int find(int key) {
        int hash_value = hash(key);
        int next = table[hash_value];

        while (next && key != database[next].key)
            next = database[next].next;
        return next;
    }

    int operator[](int key) {
        int ret = find(key);
        if (ret == 0) {
            emplace(key, cnt);
            return cnt++;
        }
        return ret;
    }
};

HashMap map;    // int (data ID) -> int (user_data index)

int main()
{

    cnt_data = 0;
    map.clear();

    map.emplace(11, 0);
    map.emplace(12, 1);
    map.emplace(13, 2);

    map.emplace(21, 3);
    map.emplace(22, 4);
    map.emplace(23, 5);

    map.emplace(31, 6);
    map.emplace(32, 7);
    map.emplace(33, 8);

    int idx;
    idx = map.find(11);
    idx = map.find(21);
    idx = map.find(31);
    idx = map.find(41);

    return 0;
}
#endif