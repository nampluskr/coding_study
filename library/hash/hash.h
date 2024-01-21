#pragma once

#define MAX_TABLE   11      // use prime number

template<typename T>
struct LinkedList {
    struct Node {
        T data = {};
        Node* next = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void clear() { while (head != nullptr) pop_front(); }
    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) { tail = nullptr; }
    }
};

template<typename T>
int hashfunc(T key) { return key % MAX_TABLE; }

// Explicit template specialization for hashfunc()
template<> int hashfunc(const char* key) {
    unsigned long long hash = 5381;
    int c;
    while (c = *key++) { hash = (((hash << 5) + hash) + c) % MAX_TABLE; }
    return hash % MAX_TABLE;
}

template<typename Key, typename Data>
struct HashMap {
    struct Pair {
        Key key;
        Data data;
    };
    LinkedList<Pair> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    void emplace(const Key& key, const Data& data) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, data });
    }
    Pair* find(const Key& key) {
        int hash = hashfunc(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next)
            if (ptr->data.key == key)
                return &ptr->data;  // { key, data }
        return nullptr;
    }
    Data& operator[](const Key& key) {
        auto ptr = find(key);
        if (ptr == nullptr) {
            int hash = hashfunc(key);
            table[hash].push_back({ key, {} });
            return table[hash].tail->data.data;
        }
        else { return ptr->data; }
    }
};