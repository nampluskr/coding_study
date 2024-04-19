#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
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
        else if (key > node->key)
            node->right = addRec(node->right, key);

        return node;
    }

    void add(const T& key) {
        current = addRec(current, key);
    }

    bool findRec(Node *node, const T& key) {
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
        else if (key > node->key)
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

    // ==================================================================
    Node *maxValueNode(Node *node) {
        Node *current = node;

        while (current->right != NULL)
            current = current->right;

        return current;
    }
    Node* clearRec(Node* curr) {
        if (curr == nullptr) return nullptr;
        curr->left = clearRec(curr->left);
        curr->right = clearRec(curr->right);
        delete curr;
        return nullptr;
    }
    void clear() { current = clearRec(current);}
    bool find(const T& key) { return findRec(current, key);}
    void insert(const T& key) { add(key); }
    T getMin() { return minValueNode(current)->key; }
    T getMax() { return maxValueNode(current)->key; }
    bool empty() { return current == NULL; }
};

struct Data {
    int value, id;
    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && id > data.id);
    }
    bool operator>(const Data& data) const {
        return (value > data.value) || (value == data.value && id < data.id);
    }
    bool operator==(const Data& data) const {
        return value == data.value && id == data.id;
    }
};

Set<Data> S;

int main(void)
{
    bool is_empty;

    is_empty = S.empty();
    S.clear();
    is_empty = S.empty();
    S.insert({ 20, 1 });
    S.insert({ 30, 3 });
    S.insert({ 10, 2 });
    is_empty = S.empty();

    S.clear();
    S.insert({ 20, 1 });
    S.insert({ 30, 3 });
    S.insert({ 10, 2 });

    // S.remove({ 20, 1 });
    // S.remove({ 30, 3 });
    // S.remove({ 10, 2 });

    auto min = S.getMin();
    auto max = S.getMax();


    return 0;
}