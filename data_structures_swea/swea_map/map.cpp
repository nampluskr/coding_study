// #include<stdio.h>
#include<malloc.h>

template<typename Key, typename Value=int>
struct Map {
    typedef struct Node {
        Key key;
        Value value;
        Node *left, *right;
    };

    Node *newNode(const Key& k, const Value& v) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->key = k;
        temp->value = v;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node *current;

    Node *putRec(Node *node, const Key& key, const Value& value) {
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

    Node* findRec(Node *node, const Key& key) {
        if (node != NULL) {
            if (key == node->key)
                return node;

            Node* ret = nullptr;
            ret = findRec(node->left, key);
            if (ret != nullptr)
                return ret;

            ret = findRec(node->right, key);
            if (ret != nullptr)
                return ret;
        }

        return nullptr;
    }

    // bool contains(const Key& key) {
    //     int ret = findRec(current, key);
    //     if (ret != -1)
    //         return true;
    //     return false;
    // }

    int get(const Key& key) {
        return findRec(current, key);
    }

    Node *minValueNode(Node *node) {
        Node *current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node *removeRec(Node *node, const Key& key) {
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
            node->value = temp->value;
            node->right = removeRec(node->right, temp->key);
        }

        return node;
    }

    void remove(const Key& key) {
        current = removeRec(current, key);
    }

    // ====================================================================
    Node* clearRec(Node* curr) {
        if (curr == nullptr) return nullptr;
        curr->left = clearRec(curr->left);
        curr->right = clearRec(curr->right);
        delete curr;
        return nullptr;
    }
    void clear() { current = clearRec(current); }
    Node* find(const Key& key) { return findRec(current, key); }
    void insert(const Key& key, const Value& value) { put(key, value); }
    bool empty() { return current == 0; }
    Value& operator[](const Key& key) {
        auto ret = find(key);
        if (ret == nullptr) {
            insert(key, -1);
            return find(key)->value;
        }
        return ret->value;
    }
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

Map<Data, int> map;

int main(void)
{
    map.clear();
    map.insert({ 20, 2 }, 2);
    map.insert({ 10, 1 }, 1);
    map.insert({ 30, 3 }, 3);

    auto value = map[{ 20, 2 }];
    map[{ 20, 2 }] = 200;
    map[{ 50, 5 }] = 5;

    // map.remove(20);
    // map.remove(10);
    map.clear();
    return 0;
}