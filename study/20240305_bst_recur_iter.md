### [BST - recursive] 4 types

```cpp
#pragma once

#include "node.h"

template<typename T>
struct BinarySearchTree_recur {
    Node<T>* root;

    Node<T>* find(const T& data) { return find(root, data); }
    void insert(const T& data) { root = insert(root, data); }
    void remove(const T& data) { root = remove(root, data); }

    Node<T>* find(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr;
        
        if (data == ptr->data) return ptr;

        if (data == ptr->data) return find(ptr->left, data);
        else return find(ptr->right, data);
    }
    Node<T>* insert(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return new Node<T>{ data, nullptr, nullptr };
        
        if (data == ptr->data) return ptr;

        if (data < ptr->data) ptr->left = insert(ptr->left, data);
        else ptr->right = insert(ptr->right, data);
        return ptr;
    }
    Node<T>* find_min(Node<T>* ptr) {
        if (ptr->left == nullptr) return ptr;
        return find_min(ptr->left);
    }
    Node<T>* find_max(Node<T>* ptr) {
        if (ptr->right == nullptr) return ptr;
        return find_max(ptr->right);
    }
    Node<T>* remove(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr;

        // [type-1]
        //if (data == ptr->data) {
        //    if (ptr->left == nullptr) {
        //        Node<T>* temp = ptr->right;
        //        delete ptr;
        //        return temp;
        //    }
        //    else if (ptr->right == nullptr) {
        //        Node<T>* temp = ptr->left;
        //        delete ptr;
        //        return temp;
        //    }
        //    else {
        //        Node<T>* succParent = ptr;
        //        Node<T>* succ = ptr->right;
        //        while (succ->left != nullptr) {
        //            succParent = succ;
        //            succ = succ->left;
        //        }
        //        ptr->data = succ->data;
        //        if (succParent == succ)
        //            succParent->left = succ->right;
        //        else
        //            succParent->right = succ->right;

        //        delete succ;
        //        return ptr;
        //    }
        //}

        // [type-2]
        if (data == ptr->data) {
            //if (ptr->left == nullptr && ptr->right == nullptr) {
            //    delete ptr;
            //    return nullptr;
            //}
            if (ptr->left == nullptr) {
                Node<T>* temp = ptr->right; delete ptr;
                return temp;
            }
            else if (ptr->right == nullptr) {
                Node<T>* temp = ptr->left; delete ptr;
                return temp;
            }
            else { // succ => ptr and delete succ
                Node<T>* succ = find_min(ptr->right);
                ptr->data = succ->data;
                ptr->right = remove(ptr->right, succ->data);
            }
        }

        //// [type-3]
        //if (data == ptr->data) {
        //    Node<T>* temp = ptr;
        //    if (ptr->left == nullptr && ptr->right == nullptr) ptr = nullptr;
        //    else if (ptr->left == nullptr) ptr = ptr->right;
        //    else if (ptr->right == nullptr) ptr = ptr->left;
        //    else {
        //        Node<T>* succ = find_min(ptr->right);
        //        ptr->right = ptr->right->right;
        //        succ->left = ptr->left;
        //        succ->right = ptr->right;
        //        ptr = succ;
        //    }
        //    delete temp;
        //    return ptr;
        //}

        // [type-4] 안됨
        //if (data == ptr->data) {
        //    if (ptr->left == nullptr && ptr->right == nullptr) {
        //        ptr = nullptr;
        //    }
        //    else if (ptr->left == nullptr) {
        //        Node<T>* succ = find_min(ptr->right);
        //        ptr->data = succ->data;
        //        ptr->right = remove(ptr->right, succ->data);
        //    }
        //    else if (ptr->right == nullptr) {
        //        Node<T>* pred = find_max(ptr->right);
        //        ptr->data = pred->data;
        //        ptr->left = remove(ptr->left, pred->data);
        //    }
        //    return ptr;
        //}

        if (data < ptr->data) ptr->left = remove(ptr->left, data);
        else ptr->right = remove(ptr->right, data);
        return ptr;
    }
};
```

### [BST - iterative] 

```cpp
#pragma once

#include "node.h"

template<typename T>
struct BinarySearchTree_iter {
    Node<T>* root;

    Node<T>* find(const T& data) {
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return ptr;
            
            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return;

            prev = ptr;
            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }

        // (ptr == nullptr) => insert data into prev node
        Node<T>* node = new Node<T>{ data, nullptr, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) break;

            prev = ptr; 
            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
        if (ptr == nullptr) return;

        // (data == ptr->data) delete ptr
        //if (ptr->left == nullptr && ptr->right == nullptr) {   // no child
        //    if (prev == nullptr) root = nullptr;
        //    else if (prev->left == ptr) prev->left = nullptr;
        //    else prev->right = nullptr;
        //}
        if (ptr->left == nullptr) {         // right child or no child
            if (prev == nullptr) root = ptr->right;
            else if (prev->left == ptr) prev->left = ptr->right;
            else prev->right = ptr->right;
        }
        else if (ptr->right == nullptr) {   // left child
            if (prev == nullptr) root = ptr->left;
            else if (prev->left == ptr) prev->left = ptr->left;
            else prev->right = ptr->left;
        }
        else {                              // 2 children
            Node<T>* succ_prev = ptr;
            Node<T>* succ = ptr->right;
            while (succ->left != nullptr) {
                succ_prev = succ;
                succ = succ->left;
            }
            ptr->data = succ->data;
            if (succ_prev->left == succ)
                succ_prev->left == succ->right;
            else
                succ_prev->right = succ->right;
            ptr = succ;
        }
        delete ptr;
    }
};
```

### [test_bst]

```cpp
#include "bst_recur.h"
#include "bst_iter.h"
#include <cstdio>

BinarySearchTree_iter<int> bst1;
BinarySearchTree_recur<int> bst2;

/*
          50
       /     \
      30      70
     /  \    /  
   20   40  60 
*/

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;
   
    inorder(ptr->left);
    printf("[%d] ", ptr->data);
    inorder(ptr->right);
}

void show(Node<int>* ptr) {
    printf(">> ");
    inorder(ptr);
    printf("\n");
}


void test_bst_recur(int option) {
    if (option == 0) return;

    bst1.insert(50);
    bst1.insert(30);
    bst1.insert(20);
    bst1.insert(40);
    bst1.insert(70);
    bst1.insert(60);
    show(bst1.root);

    printf("\n- Delete leaf node (20):\n");
    bst1.remove(20);
    show(bst1.root);

    printf("\n- Delete single child node (70):\n");
    bst1.remove(70);
    show(bst1.root);

    printf("\n- Delete two children node (50):\n");
    bst1.remove(50);
    show(bst1.root);
}

void test_bst_iter(int option) {
    if (option == 0) return;

    bst2.insert(50);
    bst2.insert(30);
    bst2.insert(20);
    bst2.insert(40);
    bst2.insert(70);
    bst2.insert(60);
    show(bst2.root);

    printf("\n- Delete leaf node (20)\n");
    bst2.remove(20);
    show(bst2.root);

    printf("\n- Delete single child node (70)\n");
    bst2.remove(70);
    show(bst2.root);

    printf("\n- Delete two children node (50)\n");
    bst2.remove(50);
    show(bst2.root);
}
```

### [main]

```cpp
#include <cstdio>

extern void test_bst_recur(int);
extern void test_bst_iter(int);

int main()
{
    printf("\n*** Binary Search Tree [Recursive] ***\n");
    test_bst_recur(1);

    printf("\n*** Binary Search Tree [Iterative] ***\n");
    test_bst_iter(1);

    return 0;
}
```
