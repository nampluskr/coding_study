#include "linked_list.h"

#define MAX_TABLE 17

template<typename T1, typename T2>
struct HashMap {
    struct Pair {
        T1 key;
        T2 value;
        bool operator==(const Pair& pair) const { return key == pair.key; }
    };
    LinkedList<Pair> table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    void insert(const T1& key, const T2& value) {
        int hash_value = key.hash(MAX_TABLE);
        table[hash_value].insert({ key, value });
    }
    Pair* find(const T1& key) {
        int hash_value = key.hash(MAX_TABLE);
        auto res = table[hash_value].find({ key, {} });
        if (res != nullptr)
            return &res->data;
        return nullptr;
    }
    void erase(const T1& key) {
        int hash_value = key.hash(MAX_TABLE);
        table[hash_value].erase({ key, {} });
    }
    T2& operator[](const T1& key) {
        auto res = find(key);
        if (res == nullptr) {
            insert(key, {});
            res = find(key);
        }
        return res->value;
    }
};