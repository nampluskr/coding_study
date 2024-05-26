### [linked_list.h] Iterator 구현

```cpp
#pragma once

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int cnt = 0;

    void clear() { 
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        cnt = 0;
    }
    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        cnt++;
    }
    T front() { return head->data; }
    T back() { return tail->data; }
    bool empty() { return head == nullptr;  }
    int size() { return cnt; }

    struct Iterator {
        Node* ptr;

        Iterator(Node* ptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
        bool operator==(const Iterator& iter) const { return ptr == iter.ptr; }
        T& operator*() { return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }
        Iterator operator++(int) { Iterator iter = *this; ptr = ptr->next; return iter; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

```

### [array_list.h] Iterator 구현

```cpp
#pragma once

template<typename T, int max_size>
struct ArrayList {
    T arr[max_size];
    int head = 0;
    int tail = 0;

    void clear() { tail = 0; }
    void push_back(const T& data) { arr[tail++] = data; }
    T front() { return arr[head]; }
    T back() { return arr[tail - 1]; }
    bool empty() { return head == tail; }
    int size() { return tail - head; }

    // iterators
    T* begin() { return &arr[head]; }
    T* end() { return &arr[tail]; }
};
```

### [main.cpp] test code

```cpp
#include <vector>
#include "linked_list.h"
#include "array_list.h"
using namespace std;

struct Data {
    int value, idx;
};

vector<Data> vec;
LinkedList<Data> sll;
ArrayList<Data, 20> arr;

template<typename T>
void test_list(T& li) {
    li.clear();
    li.push_back({ 10, 1 });
    li.push_back({ 20, 2 });
    li.push_back({ 30, 3 });
    li.push_back({ 40, 4 });
    li.push_back({ 50, 5 });

    printf(">> ");
    for (auto iter = li.begin(); iter != li.end(); iter++) {
        auto data = *iter;
        printf("(%d, %d) ", data.value, data.idx);
    }
    printf("\n");


    printf(">> ");
    for (const auto& data : li)
        printf("(%d, %d) ", data.value, data.idx);
    printf("\n");

    printf(">> front() = (%d, %d)\n", li.front().value, li.front().idx);
    printf(">> back()  = (%d, %d)\n", li.back().value, li.back().idx);

    if (!li.empty())
        li.clear();
}

int main()
{
    printf("\n[vector]\n");
    test_list(vec);

    printf("\n[Linked list]\n");
    test_list(sll);

    printf("\n[Array list]\n");
    test_list(arr);

    return 0;
}
```
