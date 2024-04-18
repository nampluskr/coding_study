### [Hash Table] 직접 구현 - Linked List 이용

```python
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
        return (h1 ^ (h2 << 1) ) % MAX_TABLE;
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

### [Priority Queue] SWEA Wrapping

```python
#if 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_SIZE 100

template<typename T>
struct PQRef {
    T heap[MAX_SIZE];
    int heapSize = 0;

    void heapInit(void)
    {
        heapSize = 0;
    }

    int heapPush(const T& value)
    {
        if (heapSize + 1 > MAX_SIZE)
        {
            printf("queue is full!");
            return 0;
        }

        heap[heapSize] = value;

        int current = heapSize;
        while (current > 0 && heap[current] < heap[(current - 1) / 2])
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
        if (heapSize <= 0)
        {
            return -1;
        }

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
                child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
            }

            if (heap[current] < heap[child])
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
};

template<typename T>
struct PriorityQueue {
    PQRef<T>* Q;    // Min. Heap (operator<)

    PriorityQueue() { Q = new PQRef<T>(); }
    ~PriorityQueue() { delete Q; }

    void push(const T& data) { Q->heapPush(data); }
    void pop() { T temp;  Q->heapPop(&temp); }
    T top() { return Q->heap[0]; }
    bool empty() { return Q->heapSize == 0; }
};

struct Data {
    int value;
    int id;
    bool operator<(const Data& data) const { 
        return (value > data.value) || (value == data.value && id < data.id);
    }
};

PriorityQueue<Data> Q;

int main(int argc, char* argv[])
{
    if (0) {
        setbuf(stdout, NULL);
        freopen("sample_input.txt", "r", stdin);

        int T, N;
        scanf("%d", &T);

        for (int test_case = 1; test_case <= T; test_case++)
        {
            scanf("%d", &N);

            //Q.clear();
            while (!Q.empty()) Q.pop();

            for (int i = 0; i < N; i++)
            {
                int value;
                scanf("%d", &value);
                Q.push(Data{ value });
            }

            printf("#%d ", test_case);

            for (int i = 0; i < N; i++)
            {
                //int value;
                //Q.heapPop(&value);
                auto value = Q.top(); Q.pop();
                printf("%d ", value.value);
            }
            printf("\n");
        }
    }

    while (!Q.empty()) Q.pop();

    Q.push({ 10, 2});
    Q.push({ 10, 1 });
    Q.push({ 20, 3});
    Q.push({ 30, 4});

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();
        printf("(%d, %d)\n", cur.value, cur.id);
    }

    return 0;
}
#endif
```

### [map] BST

```python
#if 1
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

template<typename Key, typename Value>
struct MapRef {
    typedef struct Node {
        Key key;
        Value value;
        Node* left, * right;
    };

    Node* newNode(Key k, Value v) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->key = k;
        temp->value = v;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node* current;

    Node* putRec(Node* node, const Key& key, int value) {
        if (node == NULL)
            return newNode(key, value);

        if (key < node->key)
            node->left = putRec(node->left, key, value);
        else if (key > node->key)
            node->right = putRec(node->right, key, value);
        else
            node->value = value;

        return node;
    }
    void put(const Key& key, const Value& value) {
        current = putRec(current, key, value);
    }
    Node* findRec(Node* node, const Key& key) {
        if (node != NULL) {
            if (key == node->key)
                return node;

            Node* ret = NULL;
            ret = findRec(node->left, key);
            if (ret != NULL)
                return ret;

            ret = findRec(node->right, key);
            if (ret != NULL)
                return ret;
        }

        return NULL;
    }
    bool contains(const Key& key) {
        auto ret = findRec(current, key);
        if (ret != NULL)
            return true;
        return false;
    }
    Value get(const Key& key) {
        auto ret = findRec(current, key);
        if (ret != NULL)
            return ret->value;
        return -1;
    }
    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }
    Node* removeRec(Node* node, const Key& key) {
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
            node->value = temp->value;
            node->right = removeRec(node->right, temp->key);
        }

        return node;
    }
    void remove(const Key& key) {
        current = removeRec(current, key);
    }
};

template<typename Key, typename Value>
struct Map {
    MapRef<Key, Value>* M;
    
    Map() { M = new MapRef<Key, Value>; }
    ~Map() { delete M; }
    void clear() { M->current = NULL; }
    void insert(const Key& key, int value) { M->put(key, value); }
    void remove(const Key& key) { M->remove(key); }
    Value find(const Key& key) { return M->get(key); }
};


Map<int, int> map;

int main(void) {

    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, N;
    scanf("%d", &T);

    for (int test_case = 1; test_case <= T; ++test_case) {

        //map.M->current = NULL;
        map.clear();
        scanf("%d", &N);
        printf("#%d ", test_case);

        for (int i = 0; i < N; ++i) {

            int cmd, key, value;
            scanf("%d%d", &cmd, &key);

            switch (cmd) {
            case 1:
                scanf("%d", &value);
                map.insert(key, value);
                break;
            case 2:
                map.remove(key);
                break;
            case 3:
                int ret = map.find(key);
                printf("%d ", ret);
            }
        }
        printf("\n");
    }
}
#endif
```

### [set] BST 이용

```python
#if 1
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

template<typename Key>
struct SetRef {
    typedef struct Node {
        Key key;
        Node* left, * right;
    };

    Node* newNode(const Key& key) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->key = key;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node* current;

    Node* addRec(Node* node, const Key& key) {
        if (node == NULL)
            return newNode(key);

        if (key < node->key)
            node->left = addRec(node->left, key);
        else if (key > node->key)
            node->right = addRec(node->right, key);

        return node;
    }

    void add(const Key& key) {
        current = addRec(current, key);
    }

    Node* findRec(Node* node, const Key& key) {
        if (node != NULL) {
            if (key == node->key)
                return node;
            if (findRec(node->left, key))
                return true;
            if (findRec(node->right, key))
                return true;
        }
        return NULL;
    }
    Node* find(const Key& key) {
        return findRec(current, key);
    }

    bool contains(const Key& key) {
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
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* removeRec(Node* node, const Key& key) {
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

    void remove(const Key& key) {
        current = removeRec(current, key);
    }
};

template<typename Key>
struct Set {
    SetRef<Key>* S;

    Set() { S = new SetRef<Key>(); }
    ~Set() { delete S; }
    void clear() { S->current = NULL; }
    void insert(const Key& key) { S->add(key); }
    void remove(const Key& key) { S->remove(key); }
    void print() { S->printAll(); }

};

Set<int> set;

int main(void) {

    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, N;

    scanf("%d", &T);

    for (int test_case = 1; test_case <= T; ++test_case) {

        set.clear();
        scanf("%d", &N);

        for (int i = 0; i < N; ++i) {

            int cmd, key;

            scanf("%d%d", &cmd, &key);

            switch (cmd) {
            case 1:
                set.insert(key);
                break;
            case 2:
                set.remove(key);
                break;
            }
        }

        printf("#%d ", test_case);
        set.print();
        printf("\n");
    }
}
#endif
```


### [deque]

```python
#if 1
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX 100

template<typename T>
struct DequeRef {
    T arr[MAX];
    int front;
    int rear;
    int size;

    void dequeInit(int n) {
        front = -1;
        rear = 0;
        size = n;
    }

    bool isFull() {
        return ((front == 0 && rear == size - 1) || front == rear + 1);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void insertFront(const T& value) {
        if (isFull()) {
            printf("Overflow\n");
        }

        if (front == -1) {
            front = rear = 0;
        }
        else if (front == 0) {
            front = size - 1;
        }
        else {
            front = front - 1;
        }

        arr[front] = value;
    }

    void insertRear(const T& value) {
        if (isFull()) {
            printf("Overflow\n");
        }

        if (front == -1) {
            front = rear = 0;
        }
        else if (rear == size - 1) {
            rear = 0;
        }
        else {
            rear = rear + 1;
        }

        arr[rear] = value;
    }

    T getFront() {
        if (isEmpty()) {
            printf("Underflow\n");
            return -1;
        }
        return arr[front];
    }

    T getRear() {
        if (isEmpty() || rear < 0) {
            printf("Underflow\n");
            return -1;
        }
        return arr[rear];
    }

    void deleteFront() {
        if (isEmpty()) {
            printf("Underflow\n");
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (front == size - 1) {
            front = 0;
        }
        else {
            front = front + 1;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            printf("Underflow\n");
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (rear == 0) {
            rear = size - 1;
        }
        else {
            rear = rear - 1;
        }
    }
};

template<typename T>
struct Deque {
    DequeRef<T>* Q;

    Deque() { Q = new DequeRef<T>(); }
    ~Deque() { delete Q; }

    void init(int n) { Q->dequeInit(n); }
    void push_front(const T& value) { Q->insertFront(value); }
    void push_back(const T& value) { Q->insertRear(value); }
    T front() { return Q->getFront(); }
    T back() { return Q->getRear(); }
    void pop_front() { Q->deleteFront(); }
    void pop_back() { Q->deleteRear(); }
};

Deque<int> Q;

int main(void) {

    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, N, M;

    scanf("%d", &T);

    for (int test_case = 1; test_case <= T; ++test_case) {

        scanf("%d%d", &N, &M);

        //Q.dequeInit(N);
        Q.init(N);

        printf("#%d ", test_case);

        for (int i = 0; i < M; ++i) {

            int cmd, elem;

            scanf("%d", &cmd);

            switch (cmd) {
            case 1:
                scanf("%d", &elem);
                Q.push_front(elem);
                break;
            case 2:
                scanf("%d", &elem);
                Q.push_back(elem);
                break;
            case 3:
                printf("%d ", Q.front());
                break;
            case 4:
                printf("%d ", Q.back());
                break;
            case 5:
                Q.pop_front();
                break;
            case 6:
                Q.pop_back();
                break;
            }
        }

        printf("\n");
    }

    return 0;
}
#endif
```
