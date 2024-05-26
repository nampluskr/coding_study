#pragma once

#include <malloc.h>

template<typename T1, typename T2>
struct Map {
    struct Node {
        T1 key;
        T2 value;
        Node *left, *right;
    };
    
    Node *newNode(const T1 key, const T2 value) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->key = key;
        temp->value = value;
        temp->left = temp->right = NULL;
        return temp;
    }
    
    Node *current;
    
    Node *putRec(Node *node, const T1& key, const T2& value) {
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
    
    void put(const T1& key, const T2& value) {
        current = putRec(current, key, value);
    }
    
    // int findRec(Node *node, const T1& key) {
    //     if (node != NULL) {
    //         if (key == node->key)
    //             return node->value;
    
    //         int ret = -1;
    //         ret = findRec(node->left, key);
    //         if (ret != -1)
    //             return ret;
    
    //         ret = findRec(node->right, key);
    //         if (ret != -1)
    //             return ret;
    //     }
    
    //     return -1;
    // }
    
    // bool contains(const T1& key) {
    //     int ret = findRec(current, key);
    //     if (ret != -1)
    //         return true;
    //     return false;
    // }
    
    // int get(const T1& key) {
    //     return findRec(current, key);
    // }
    
    Node *minValueNode(Node *node) {
        Node *current = node;
    
        while (current->left != NULL)
            current = current->left;
    
        return current;
    }
    
    Node *removeRec(Node *node, const T1& key) {
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

    void remove(const T1& key) { 
        current = removeRec(current, key);
    }

    // [User defined methods] =======================================
    Node* clear(Node* node) {
        if (node == nullptr) return nullptr;
        node->left = clear(node->left);
        node->right = clear(node->right);
        free(node);
        return nullptr;
    }
    void clear() { current = clear(current); }
    Node* find(const T1& key) {
        Node* cur = current;
        while (cur != nullptr) {
            if (cur->key == key) return cur;
            if (cur->key < key) cur = cur->right; 
            else if (key < cur->key) cur = cur->left;
        }
        return nullptr;
    }
    void insert(const T1& key, const T2& value) { put(key, value); }
    void erase(const T1& key) { remove(key); }
    T2& operator[](const T1& key) {
        auto res = find(key);
        if (res == nullptr) {
            insert(key, {});
            res = find(key);
        }
        return res->value;
    }
};