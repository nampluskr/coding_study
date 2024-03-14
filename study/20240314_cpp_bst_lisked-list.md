### [BST] bst.h

```cpp
#pragma once

#include <queue>
#include <stack>

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

template<typename T>
struct BST_recur {
    Node<T>* root;

    void clear() { root = clear(root); }
    Node<T>* find(const T& data) { return find(data); }
    void insert(const T& data) { root = insert(root, data); }
    void remove(const T& data) { root = remove(root, data); }

    Node<T>* clear(Node<T>* cur) {
        if (cur == nullptr) return nullptr;
        cur->left = clear(cur->left);
        cur->right = clear(cur->right);
        // postorder traversal
        delete cur;
        return nullptr;
    }
    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        if (data < curr->data) return find(curr->left, data);
        else return find(curr->right, data);
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<T>{data, nullptr};
        if (data == curr->data) return nullptr;
        if (data < curr->data) curr->left = insert(curr->left, data);
        else curr->right = insert(curr->right, data);
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            if (curr->left == nullptr && curr->right == nullptr) {
                delete curr;
                return nullptr;
            }
            else if (curr->right == nullptr) {
                auto temp = curr->left;
                delete curr;
                return temp;
            }
            else if (curr->left == nullptr) {
                auto temp = curr->right;
                delete curr;
                return temp;
            }
            else {
                // find the successor of curr node
                auto succ = findMinNode(curr->right);
                curr->data = succ->data;
                curr->right = remove(curr->right, succ->data);
            }
        }
        if (data < curr->data) curr->left = remove(curr->left, data);
        else curr->right = remove(curr->right, data);
        return curr;
    }
    Node<T>* findMinNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        if (curr->left == nullptr) return curr;
        return findMinNode(curr->left);
    }
};

template<typename T>
struct BST_iter{
    Node<T>* root;

    //void clear() {            // delete nodes in level order
    //    std::queue<Node<T>*> Q;
    //    Q.push(root);
    //    while (!Q.empty()) {
    //        auto curr = Q.front(); Q.pop();
    //        if (curr->left != nullptr) Q.push(curr->left);
    //        if (curr->right != nullptr) Q.push(curr->right);
    //        delete curr;
    //    }
    //    root = nullptr;
    //}
    void clear() {              // delete nodes in preorder
        std::stack<Node<T>*> S;
        S.push(root);
        while (!S.empty()) {
            auto curr = S.top(); S.pop();
            if (curr->left != nullptr) S.push(curr->left);
            if (curr->right != nullptr) S.push(curr->right);
            delete curr;
        }
        root = nullptr;
    }
    Node<T>* find(const T& data) {
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }

        // curr == nullptr
        auto node = new Node<T>{ data, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (curr == nullptr) return;

        // data == curr->data
        if (curr->left == nullptr && curr->right == nullptr) {
            if (prev == nullptr) root = nullptr;
            else if (data < prev->data) prev->left = nullptr;
            else prev->right = nullptr;
        }
        else if (curr->right == nullptr) {
            if (prev == nullptr) root = curr->left;
            else if (data < prev->data) prev->left = curr->left;
            else prev->right = curr->left;
        }
        else if (curr->left == nullptr) {
            if (prev == nullptr) root = curr->right;
            else if (data < prev->data) prev->left = curr->right;
            else prev->right = curr->right;
        }
        else {
            // find the successor of curr node
            Node<T>* succ_prev = curr;
            Node<T>* succ = curr->right;
            while (succ->left != nullptr) {
                succ_prev = succ;
                succ = succ->left;
            }
            curr->data = succ->data;
            if (succ_prev->left == succ) succ_prev->left = succ->right;
            else succ_prev->right = succ->right;
            curr = succ;    // delete succ
        }
        delete curr;
    }
};
```

### [BST] bst.cpp

```cpp
#include <cstdio>
#include "bst.h"
#include <stack>
#include <queue>

BST_recur<int> bst1;
BST_iter<int> bst2;

void inorder(Node<int>* curr) {
    if (curr == nullptr) return;
    if (curr->left != nullptr) inorder(curr->left);
    printf("[%d] ", curr->data);
    if (curr->right != nullptr) inorder(curr->right);
}

void preorder(Node<int>* curr) {
    if (curr == nullptr) return;
    printf("[%d] ", curr->data);
    if (curr->left != nullptr) preorder(curr->left);
    if (curr->right != nullptr) preorder(curr->right);
}

void preorder_stack(Node<int>* root) {
    printf(">> ");
    if (root == nullptr) return;
    std::stack<Node<int>*> S;
    S.push(root);

    while (!S.empty()) {
        auto curr = S.top(); S.pop();

        printf("[%d] ", curr->data);
        if (curr->right != nullptr) S.push(curr->right);
        if (curr->left != nullptr) S.push(curr->left);
    }
    printf("\n");
}

void levelorder(Node<int>* root) {
    printf(">> ");
    if (root == nullptr) return;
    std::queue<Node<int>*> Q;
    Q.push(root);

    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();

        printf("[%d] ", curr->data);
        if (curr->left != nullptr) Q.push(curr->left);
        if (curr->right != nullptr) Q.push(curr->right);
    }
    printf("\n");
}

template<typename T>
void show(const T& bst) {
    printf(">> ");
    preorder(bst.root);
    printf("\n");

    preorder_stack(bst.root);
    
    levelorder(bst.root);
    printf("\n");
}

template<typename T>
void test_BST(T& bst) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(1);
    bst.insert(7);
    bst.insert(10);
    show(bst);

    //bst.clear();
    //show(bst);

    bst.remove(1);
    show(bst);

    bst.remove(10);
    show(bst);

    bst.remove(5);
    show(bst);
}

void test_BST_recur() { test_BST(bst1); }
void test_BST_iter() { test_BST(bst2); }
```

### [BST] main.cpp

```cpp
#include <cstdio>
#include "bst.h"

extern void test_BST_recur();
extern void test_BST_iter();

int main()
{
    printf("\n*** Binary Search Tree - [Recursive]\n");
    test_BST_recur();

    printf("\n*** Binary Search Tree - [Iterative]\n");
    test_BST_iter();

    return 0;
}
```

### [SLL] sll.h

```cpp
#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct OrderedSLL_recur {
    Node<T>* head;

    Node<T>* find(const T& data) { return find(head, data); }
    void insert(const T& data) { head = insert(head, data); }
    void remove(const T& data) { head = remove(head, data); }

    Node<T>* find(Node<T>* curr, const T& data) { 
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        if (data < curr->data) return find(curr->next, data);
        else return nullptr;
    }
    Node<T>* insert(Node<T>* curr, const T& data) { 
        if (curr == nullptr) return new Node<T>{ data, nullptr };
        if (data == curr->data) return curr;
        if (data < curr->data) curr->next = insert(curr->next, data);
        else {
            curr = new Node<T>{ data, curr };
            //Node<T>* node = new Node<T>{ data, nullptr };
            //node->next = curr;
            //curr = node;
        }
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) { 
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            auto temp = curr;
            curr = curr->next;
            //if (curr->next == nullptr) curr = nullptr;
            //else curr = curr->next;
            delete temp;
            return curr;
        };
        if (data < curr->data) curr->next = remove(curr->next, data);
        else curr = nullptr;
        return curr;
    }
};

template<typename T>
struct OrderedSLL_iter {
    Node<T>* head;

    Node<T>* find(const T& data) {
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            if (data < curr->data) curr = curr->next;
            else break;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return;
            if (data < curr->data) {
                prev = curr;
                curr = curr->next;
            }
            else break;
        }
        Node<T>* node = new Node<T>{ data, nullptr };
        node->next = curr;
        if (prev == nullptr) { head = node; }
        else { prev->next = node; }
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->next;
            else return;
        }
        if (curr == nullptr) return;

        // data == curr->data
        if (curr->next == nullptr) {
            if (prev == nullptr) head = nullptr;
            else prev->next = nullptr;
        }
        else {
            if (prev == nullptr) head = curr->next;
            else prev->next = curr->next;
        }
        delete curr;
    }
};

template<typename T>
struct SLL_recur {
    Node<T>* head;

    Node<T>* find(const T& data) { return find(head, data); }
    void insert(const T& data) { head = insert(head, data); }
    void remove(const T& data) { head = remove(head, data); }

    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        return find(curr->next, data);
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<T>{ data, nullptr };
        if (data == curr->data) return curr;
        curr->next = insert(curr->next, data);
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            auto temp = curr;
            if (curr->next == nullptr) curr = nullptr;
            else curr = curr->next;
            delete temp;
            return curr;
        };
        curr->next = remove(curr->next, data);
        return curr;
    }
};

template<typename T>
struct SLL_iter {
    Node<T>* head;

    Node<T>* find(const T& data) {
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return;
            prev = curr;
            curr = curr->next;
        }
        Node<T>* node = new Node<T>{ data, nullptr };
        node->next = curr;
        if (prev == nullptr) { head = node; }
        else { prev->next = node; }
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return;

        // data == curr->data
        if (curr->next == nullptr) {
            if (prev == nullptr) head = nullptr;
            else prev->next = nullptr;
        }
        else {
            if (prev == nullptr) head = curr->next;
            else prev->next = curr->next;
        }
        delete curr;
    }
};
```

### [SLL] sll.cpp

```cpp
#include <cstdio>
#include "sll.h"

void preorder(Node<int>* curr) {
    if (curr == nullptr) return;
    printf("[%d] ", curr->data);
    preorder(curr->next);
}

template<typename T>
void show(const T& sll) {
    printf(">> ");
    preorder(sll.head);
    printf("\n");
}

template<typename T>
void test_SLL(T& sll) {
    sll.insert(5);
    sll.insert(3);
    sll.insert(10);
    sll.insert(7);
    sll.insert(1);
    show(sll);

    sll.remove(10);
    show(sll);

    sll.remove(5);
    show(sll);

    sll.remove(1);
    show(sll);
}

OrderedSLL_recur<int> lst1;
OrderedSLL_iter<int> lst2;
SLL_recur<int> lst3;
SLL_iter<int> lst4;

void test_OrderedSLL_recur() { test_SLL(lst1); }
void test_OrderedSLL_iter() { test_SLL(lst2); }
void test_SLL_recur() { test_SLL(lst3); }
void test_SLL_iter() { test_SLL(lst4); }
```

### [SLL] main.cpp

```cpp
extern void test_OrderedSLL_recur();
extern void test_OrderedSLL_iter();
extern void test_SLL_recur();
extern void test_SLL_iter();

int main()
{
    test_OrderedSLL_recur();
    test_OrderedSLL_iter();
    test_SLL_recur();
    test_SLL_iter();

    return 0;
}
```


