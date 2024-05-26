# Hash Chaining

## Dynamic Data Structures

```cpp
#define MAX_TABLE   17

template<typename T1, typename T2>
struct HashChaining {
    struct Pair {
        T1 key;
        T2 value;
        bool operator==(const Pair& pair) const { return key == pair.key; }
    };
    Container<Pair> table[MAX_TABLE];

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
        return table[hash_value].find({ key, {} });
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
```

### Singly Linked List

```cpp
template<typename T>
struct SinglyLinkedList{
    struct Node {
        T data;
        Node* next;
    };
    Node* head = nullptr;

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete head;
        }
    }
    void insert(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) head = node;
        else { node->next = head; head = node; }
    }
    T* find(const T& data) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }
    void erase(const T& data) {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) break;
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr) return;
        if (prev == nullptr) head = cur->next;
        else prev->next = cur->next;
        delete cur;
    }
};
```

### Doubly Linked List

```cpp
#include<malloc.h>

#define NULL (0)

template<typename T>
struct DoublyLinkedList {
    struct ListNode
    {
        T data;
        struct ListNode* prev;
        struct ListNode* next;
    };

    ListNode* list_create(const T& data = {})
    {
        ListNode* node = (ListNode*)malloc(sizeof(ListNode));

        node->prev = NULL;
        node->next = NULL;
        node->data = data;

        return node;
    }

    ListNode* list_insert(ListNode* head, ListNode* new_node)
    {
        ListNode* next = head->next;

        head->next = new_node;
        new_node->next = next;
        new_node->prev = head;

        if (next != NULL)
        {
            next->prev = new_node;
        }

        return new_node;
    }

    int list_erase(ListNode* head, const T& data)
    {
        ListNode* it = head->next;
        int ret = 0;

        while (it != NULL)
        {
            if (it->data == data)
            {
                ListNode* prev = it->prev;
                ListNode* next = it->next;
                ListNode* tmp = it;
                it = it->next;

                prev->next = next;
                if (next != NULL)
                {
                    next->prev = prev;
                }

                free(tmp);
                ret++;
            }
            else
            {
                it = it->next;
            }
        }

        return ret;
    }

    // === [User defined method] ===
    ListNode* head = head = list_create(); // dummy node

    void clear() {
         while (head != NULL) {
            ListNode* tmp = head;
            head = head->next;
            free(tmp);
         }
         head = list_create();
    }
    T* find(const T& data) {
        auto cur = head->next;
        while (cur != NULL) {
            if (cur->data == data) return &cur->data;
            cur = cur->next;
        }
        return NULL;
    }
    void insert(const T& data) {
        ListNode* node = list_create(data);
        list_insert(head, node);
    }
    int erase(const T& data) { 
        int res = list_erase(head, data);
        return res;
    }
};
```

### Binary Search Tree

```cpp
#include<malloc.h>

#define NULL (0)

template<typename T>
struct BinarySearchTree {
    struct Node {
        T key;
        Node* left, * right;
    };

    Node* newNode(const T& item) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->key = item;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node* current;

    Node* addRec(Node* node, const T& key) {
        if (node == NULL)
            return newNode(key);

        if (key < node->key)
            node->left = addRec(node->left, key);
        else if (key > node->key)
            node->right = addRec(node->right, key);

        return node;
    }

    void insert(const T& key) {
        current = addRec(current, key);
    }

    T* findRec(Node* node, const T& key) {
        if (node != NULL) {
            if (key == node->key)
                return &node->key;
            if (key < node->key)
                return findRec(node->left, key);
            else if (node->key < key)
                return findRec(node->right, key);
        }
        return NULL;
    }

    T* find(const T& key) { return findRec(current, key); }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* removeRec(Node* node, const T& key) {
        if (node == NULL)
            return node;

        if (key < node->key)
            node->left = removeRec(node->left, key);
        else if (key > node->key)
            node->right = removeRec(node->right, key);
        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                free(node);
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                free(node);
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = removeRec(node->right, temp->key);
        }

        return node;
    }

    void erase(const T& key) {
        current = removeRec(current, key);
    }
    void clearRec (Node* node) {
        if (node == nullptr) return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }
    void clear() {
        clearRec(current);
        current = nullptr;
    }
};
```

## Hash Chaining - Node{ key, value, next }

```cpp
#define MAX_TABLE   17

template<typename T1, typename T2>
struct HashChaining {
    struct Node {
        T1 key;
        T2 value;
        Node* next = nullptr;
    };
    Node* table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) {
            Node** head = &table[i];
            while (*head != nullptr) {
                Node* temp = *head;
                *head = (*head)->next;
                delete temp;
            }
        }
    }
    void insert(const T1& key, const T2& value) {
        int hash_value = key.hash(MAX_TABLE);
        Node** head = &table[hash_value];
        Node* node = new Node{ key, value, nullptr };
        if (*head == nullptr) { *head = node; }
        else { node->next = *head; *head = node; }
    }
    Node* find(const T1& key) {
        int hash_value = key.hash(MAX_TABLE);
        Node** cur = &table[hash_value];
        while (*cur != nullptr) {
            if ((*cur)->key == key) return *cur;
            *cur = (*cur)->next;
        }
        return nullptr;
    }
    void erase(const T1& key) {
        int hash_value = key.hash(MAX_TABLE);
        Node** head = &table[hash_value];
        Node** prev = head; *prev = nullptr;
        Node** cur = head;
        while (*cur != nullptr) {
            if ((*cur)->key == key) break;
            *prev = *cur;
            *cur = (*cur)->next;
        }
        if (*cur == nullptr) return;
        if (*prev == nullptr) { *head = (*cur)->next; }
        else (*prev)->next = (*cur)->next;
        delete* cur;
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
```

## Binary Serarch Tree - Node{ key, value, left, right }

```cpp
#pragma once

#include <malloc.h>
#define NULL (0)

template<typename T1, typename T2>
struct Map {
    struct Node {
        T1 key;
        T2 value;
        Node* left, * right;
    };

    Node* newNode(const T1& k, const T2& v) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->key = k;
        temp->value = v;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node* current;

    Node* insertRec(Node* node, const T1& key, const T2& value) {
        if (node == NULL)
            return newNode(key, value);

        if (key < node->key)
            node->left = insertRec(node->left, key, value);
        else if (key > node->key)
            node->right = insertRec(node->right, key, value);
        else
            node->value = value;

        return node;
    }

    void insert(const T1& key, const T2& value) {
        current = insertRec(current, key, value);
    }

    Node* findRec(Node* node, const T1& key) {
        if (node != NULL) {
            if (key == node->key)
                return node;
            if (key < node->key)
                return findRec(node->left, key);
            else if (node->key < key)
                findRec(node->right, key);
        }
        return nullptr;
    }

    Node* find(const T1& key) {
        return findRec(current, key);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* eraseRec(Node* node, const T1& key) {
        if (node == NULL)
            return node;

        if (key < node->key)
            node->left = eraseRec(node->left, key);
        else if (key > node->key)
            node->right = eraseRec(node->right, key);
        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                free(node);
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                free(node);
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = eraseRec(node->right, temp->key);
        }

        return node;
    }

    void erase(const T1& key) {
        current = eraseRec(current, key);
    }

    void clearRec(Node* node) {
        if (node == nullptr) return nullptr;
        clear(node->let);
        clear(node->right);
        free(node);
    }

    void clear() { clearRec(current); current = nullptr; }
};
```

## Test Code

```cpp
#pragma once

#include <cstdio>
#include "..\data\data.h"

template<typename T>
void test(T& map) {
    Data d1{ 10, 1 }, d2{ 20, 2 }, d3{ 30, 3 };
    auto& m = map;

    printf("\n*** [Insert] ***\n");
    m.clear();
    m.insert(d1, 1111);
    m.insert(d2, 1111);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Erase] ***\n");
    m.erase(d1);
    m.erase(d2);
    m.erase(d3);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Assign] ***\n");
    m[d1] = 111;
    m[d2] = 222;

    printf(">> map[d1] = %d\n", m[d1]);
    printf(">> map[d2] = %d\n", m[d2]);
    printf(">> map[d3] = %d\n", m[d3]);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Erase] ***\n");
    m.clear();

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    m.clear();
}
```

## Hash Chaining Using Array

```cpp
#include <cstdio>

#define MAX_DATA    20
#define MAX_TABLE   17

struct Data {
    int number, ID;
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
    int operator[](int key) {
        int res = find(key);
        if (res == 0) {
            insert(key, idx);
            return idx++;
        }
        return res;
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

    db[idx] = { 10, 1111 }; map.insert(1111, idx++);
    db[idx] = { 20, 2222 }; map.insert(2222, idx++);
    db[idx] = { 30, 3333 }; map.insert(3333, idx++);

    printf("\n=== find ===\n");
    printf("map[%d] = %d\n", 1111, map.find(1111));
    printf("map[%d] = %d\n", 2222, map.find(2222));
    printf("map[%d] = %d\n", 3333, map.find(3333));
    printf("map[%d] = %d\n", 4444, map.find(4444));
    printf("map[%d] = %d\n", 5555, map.find(5555));

    printf("\n=== operator[] ===\n");
    printf("map[%d] = %d\n", 1111, map[1111]);
    printf("map[%d] = %d\n", 2222, map[2222]);
    printf("map[%d] = %d\n", 3333, map[3333]);
    printf("map[%d] = %d\n", 4444, map[4444]);
    printf("map[%d] = %d\n", 5555, map[5555]);


    return 0;
}
```
