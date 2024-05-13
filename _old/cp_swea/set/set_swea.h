#include<malloc.h>

template<typename T>
struct Set { 
    typedef struct Node {
        T key;
        Node *left, *right;
    };
    
    Node *newNode(const T& item) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->key = item;
        temp->left = temp->right = NULL;
        return temp;
    }
    
    Node *current;
    
    Node *addRec(Node *node, const T& key) {
        if (node == NULL)
            return newNode(key);
    
        if (key < node->key)
            node->left = addRec(node->left, key);
        else if (node->key < key)
            node->right = addRec(node->right, key);
    
        return node;
    }
    
    void add(const T& key) {
        current = addRec(current, key);
    }
    
    // bool findRec(Node *node, const T& key) {
    //     if (node != NULL) {
    //         if (key == node->key)
    //             return true;
    //         if (findRec(node->left, key))
    //             return true;
    //         if (findRec(node->right, key))
    //             return true;
    //     }
    
    //     return false;
    // }
    
    // bool contains(const T& key) {
    //     return findRec(current, key);
    // }
    
    // void printAll(Node *node) {
    //     if (node != NULL) {
    //         printAll(node->left);
    //         printf("%d ", node->key);
    //         printAll(node->right);
    //     }
    // }
    
    // void printAll() {
    //     printAll(current);
    // }
    
    Node *minValueNode(Node *node) {
        Node *current = node;
    
        while (current->left != NULL)
            current = current->left;
    
        return current;
    }

    Node *removeRec(Node *node, const T& key) {
        if (node == NULL)
            return node;
    
        if (key < node->key)
            node->left = removeRec(node->left, key);
        else if (node->key < key)
            node->right = removeRec(node->right, key);
        else {
            if (node->left == NULL) {
                Node *temp = node->right;
                free(node);
                return temp;
            }
            else if (node->right == NULL) {
                Node *temp = node->left;
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

    // [User defined methods] =======================================
    void clear() {}
    Node* find(const T& key) {
        Node* cur = current;
        while (cur != nullptr) {
            if (cur->key == key) return cur;
            if (key < cur->key) cur = cur->left;
            else if (cur->key < key) cur = cur->right;
        }
        return nullptr;
    }
    void insert(const T& key) { add(key);}
    void erase(const T& key) { remove(key); }
    bool empty() { return current == nullptr; }

    Node *maxValueNode(Node *node) {
        Node *current = node;
    
        while (current->right != NULL)
            current = current->right;
    
        return current;
    }
    T front() { return minValueNode(current)->key; }
    T back() { return maxValueNode(current)->key; }
};