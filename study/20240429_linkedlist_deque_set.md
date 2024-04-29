### [LinkedList]

```cpp
#include <memory>
#include <cstdio>

template<typename T>
struct LinkedList {
    typedef struct ListNode
    {
        T data;
        struct ListNode* prev;
        struct ListNode* next;
    };

    ListNode* list_create(const T& data)
    {
        ListNode* node = (ListNode*)malloc(sizeof(ListNode));
        node->prev = nullptr;
        node->next = nullptr;
        node->data = data;

        return node;
    }

    ListNode* list_insert(ListNode* head, ListNode* new_node)
    {
        ListNode* next = head->next;
        head->next = new_node;
        new_node->next = next;
        new_node->prev = head;

        if (next != nullptr)
        {
            next->prev = new_node;
        }
        return new_node;
    }

    int list_erase(ListNode* head, const T& data)
    {
        ListNode* it = head->next;
        int ret = 0;

        while (it != nullptr)
        {
            if (it->data == data)
            {
                ListNode* prev = it->prev;
                ListNode* next = it->next;
                ListNode* tmp = it;

                it = it->next;
                prev->next = next;
                if (next != nullptr)
                {
                    next->prev = prev;
                }
                free(tmp);
                ret++;
                return ret;
            }
            else
            {
                it = it->next;
            }
        }

        return ret;
    }

    // User methods
    ListNode* head = list_create(0);
    int cnt = 0;

    void clear() {
        while (head != NULL)
        {
            ListNode* tmp = head;
            head = head->next;
            free(tmp);
        }
        head = list_create(0);
        cnt = 0;
    }
    ListNode* find(const T& data) {
        ListNode* it = head->next;
        while (it != nullptr) {
            if (it->data == data)
                return it;
            it = it->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        ListNode* node = list_create(data);
        list_insert(head, node);
        cnt++;
    }
    void remove(const T& data) {
        int ret = list_erase(head, data);
        cnt -= ret;
        printf(">> Num. of removed elements: %d\n", ret);
    }
    bool empty() { return cnt == 0; }
    int size() { return cnt; }
    T back() { return *head->next; }
    void print() {
        ListNode* it = head->next;
        while (it != nullptr) {
            printf("%d ", it->data);
            it = it->next;
        }
        printf("\n");
    }
};

LinkedList<int> L;

int main()
{
    L.clear();

    L.insert(10);   L.print();
    L.insert(100);  L.print();
    L.insert(20);   L.print();
    L.insert(100);  L.print();
    L.insert(30);   L.print();
    L.insert(100);  L.print();

    auto it = L.find(20);
    if (it != nullptr)
        it->data = -1;
    L.print();

    L.remove(100);  L.print();
    L.remove(20);   L.print();
    L.remove(10);   L.print();
    L.remove(30);   L.print();

    L.clear();

    return 0;
}
```

### [Deque]

```cpp
#include <cstdio>

#define MAX 100

template<typename T>
struct Deque {
    T arr[MAX];
    int head;
    int tail;
    int max_size ;

    void dequeInit(int n) {
        head = -1;
        tail = 0;
        max_size  = n;
    }

    bool isFull() {
        return ((head == 0 && tail == max_size  - 1) || head == tail + 1);
    }

    bool isEmpty() {
        return (head == -1);
    }

    void insertFront(const T& value) {
        if (head == -1) {
            head = tail = 0;
        }
        else if (head == 0) {
            head = max_size  - 1;
        }
        else {
            head = head - 1;
        }

        arr[head] = value;
    }

    void insertRear(const T& value) {
        if (head == -1) {
            head = tail = 0;
        }
        else if (tail == max_size  - 1) {
            tail = 0;
        }
        else {
            tail = tail + 1;
        }

        arr[tail] = value;
    }

    T getFront() {
        return arr[head];
    }

    T getRear() {
        return arr[tail];
    }

    void deleteFront() {
        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else if (head == max_size  - 1) {
            head = 0;
        }
        else {
            head = head + 1;
        }
    }

    void deleteRear() {
        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else if (tail == 0) {
            tail = max_size  - 1;
        }
        else {
            tail = tail - 1;
        }
    }

    // User methods
    void clear() { dequeInit(MAX); }
    void push_front(const T& data) { insertFront(data); }
    void push_back(const T& data) { insertRear(data); }
    void pop_front() { deleteFront(); }
    void pop_back() { deleteRear(); }
    T front() { return getFront(); }
    T back() { return getRear(); }
    bool empty() { return isEmpty(); }

};

Deque<int> Q;

int main()
{
    Q.clear();

    Q.push_back(10);
    Q.push_back(20);
    Q.push_back(30);

    Q.push_front(3);
    Q.push_front(2);
    Q.push_front(1);

    if (0) {
        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop_front();
            printf("%d ", cur);
        }
        printf("\n");
    }
    if (1) {
        while (!Q.empty()) {
            auto cur = Q.back(); Q.pop_back();
            printf("%d ", cur);
        }
        printf("\n");
    }


    Q.clear();

    return 0;
}
```

### [Set]

```cpp
#include<stdio.h>
#include<malloc.h>

template<typename T>
struct Set {
    typedef struct Node {
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

    void add(const T& key) {
        current = addRec(current, key);
    }

    bool findRec(Node* node, const T& key) {
        if (node != NULL) {
            if (key == node->key)
                return true;
            if (findRec(node->left, key))
                return true;
            if (findRec(node->right, key))
                return true;
        }

        return false;
    }

    bool contains(const T& key) {
        return findRec(current, key);
    }

    void printAll(Node* node) {
        if (node != NULL) {
            printAll(node->left);
            printf("%d ", node->key);
            printAll(node->right);
        }
    }

    void printAll() {
        printAll(current);
        printf("\n");
    }

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

    void remove(const T& key) {
        current = removeRec(current, key);
    }

    // User methods
    Node* maxValueNode(Node* node) {
        Node* current = node; 

        while (current->right != NULL)
            current = current->right;

        return current;
    }

    void clear() {}
    Node* find(const T& key) {}
    void insert(const T& key) { add(key); }
    T top() { return maxValueNode(current)->key; }
    T bottom() { return minValueNode(current)->key; }
    bool empty() {}
};

Set<int> bst;

int main()
{
    bst.insert(30);
    bst.insert(10);
    bst.insert(20);
    bst.insert(50);
    bst.insert(40);
    bst.printAll();
    printf(">> max = %d, min = %d\n", bst.top(), bst.bottom());

    bst.remove(50);
    bst.remove(30);
    bst.remove(10);
    bst.printAll();
    printf(">> max = %d, min = %d\n", bst.top(), bst.bottom());

    return 0;
}
```

### [PriorityQueue]

```cpp
#include <stdio.h>

#define MAX_SIZE 100

// Max. Heap
template<typename T>
struct PriorityQueue {
    T heap[MAX_SIZE];
    int heapSize = 0;

    void heapInit(void)
    {
        heapSize = 0;
    }

    int heapPush(const T& value)
    {
        //if (heapSize + 1 > MAX_SIZE)
        //{
        //    printf("queue is full!");
        //    return 0;
        //}

        heap[heapSize] = value;

        int current = heapSize;
        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            auto temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }

        heapSize = heapSize + 1;

        return 1;
    }

    int heapPop(T* value)
    {
        //if (heapSize <= 0)
        //{
        //    return -1;
        //}

        *value = heap[0];
        heapSize = heapSize - 1;

        heap[0] = heap[heapSize];

        int current = 0;
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }

            if (heap[child] < heap[current])
            {
                break;
            }

            auto temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            current = child;
        }
        return 1;
    }

    // User methods
    void clear() { heapInit(); }
    void push(const T& data) { heapPush(data); }
    void pop() { T temp; heapPop(&temp); }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }
    int size() { return heapSize; }
};

struct Data {
    int value, id;
    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && id > data.id);
    }
};

PriorityQueue<Data> Q;

int main()
{
    Q.clear();

    Q.push({ 50, 5 });
    Q.push({ 20, 2 });
    Q.push({ 30, 3 });
    Q.push({ 40, 4 });

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();
        printf("(%d, %d)\n", cur.value, cur.id);
    }

    return 0;
}
```
