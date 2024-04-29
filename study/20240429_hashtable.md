## hashtable

- 데이터 구조: LinkedList, BST, vector, set 비교 구현해 볼 것

```cpp
#if 1
#include <cstdio>
#include <unordered_map>
using namespace std;

#define MAX_TABLE 11

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void clear() { while (!empty()) pop_front(); }
    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    bool empty() { return head == nullptr; }
    Node* findRec(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        return findRec(node->next, data);
    }
    Node* find(const T& data) {
        return findRec(head, data);
    }
};

struct Data {
    int value, id;

    bool operator==(const Data& data) const {
        return (value == data.value) && (id == data.id);
    }
};

//LinkedList<Data> L;

template<>
struct hash<Data> {
    int operator()(const Data& data) const noexcept {
        int h1 = data.value % MAX_TABLE;
        int h2 = data.id % MAX_TABLE;
        return (h1 ^ (h2 << 1)) % MAX_TABLE;
    }
};

int hashfunc(const Data& data) {
    int h1 = data.value % MAX_TABLE;
    int h2 = data.id % MAX_TABLE;
    return (h1 ^ (h2 << 1)) % MAX_TABLE;
}

template<typename Key, typename Value>
struct HashTable {
    struct Pair {
        Key key;
        Value value;
        bool operator==(const Pair& pair) const {
            return key == pair.key;
        }
    };
    LinkedList<Pair> table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    void emplace(const Key& key, const Value& value) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, value });
    }
    Pair* find(const Key& key) {
        int hash = hashfunc(key);
        auto ptr = table[hash].find({ key, {} });
        if (ptr != nullptr)
            return &ptr->data;
        return nullptr;
    }
    Value& operator[](const Key& key) {
        auto ptr = find(key);   // Pair{ key, value }
        if (ptr == nullptr) {
            int hash = hashfunc(key);
            table[hash].push_back({ key, {} });
            return table[hash].tail->data.value;
        }
        return ptr->value;
    }
};

HashTable<Data, int> hmap;


int main()
{
    hmap.clear();
    hmap.emplace(Data{ 100, 10 }, 1);
    hmap.emplace(Data{ 200, 20 }, 2);

    auto val = hmap.find({ 200, 20 });
    hmap[{ 200, 20 }] = 2222;
    hmap[{ 300, 30 }] = 3333;

    printf("%d\n", hmap[{ 200, 20 }]);
    printf("%d\n", hmap[{ 300, 30 }]);


    return 0;
}
#endif
```

### [저장 컨테이너] vector

```cpp
struct Data {
    int number;
    bool operator==(const Data& data) const {
        return number == data.number;
    }
};


template<>
struct hash<Data> {
    int operator()(const Data& data) const noexcept {
        return data.number % MAX_TABLE;
    }
};


template<typename T1, typename T2>
struct HashMap {
    struct Pair {
        T1 key;
        T2 value;
        //bool operator==(const Pair& pair) const {
        //    return key == pair.key;
        //}
    };
    vector<Pair> table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    void emplace(const T1& key, const T2& value) {
        int h = hash<T1>()(key);
        table[h].push_back({ key, value });
    }
    Pair* find(const T1& key) {
        int h = hash<T1>()(key);
        for (auto& vec : table[h])
            if (vec.key == key)
                return &vec;
        return nullptr;
    }
    T2& operator[](const T1& key) {
        auto ptr = find(key);
        if (ptr == nullptr) {
            int h = hash<T1>()(key);
            table[h].push_back({ key, {} });
            return table[h].back().value;
        }
        return ptr->value;
    }
};
```
