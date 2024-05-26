#pragma once

#include<stdio.h>
#include<malloc.h>

template<typename T1, typename T2>
struct MapSWEA {
    struct Node {
        T1 key;
        T2 value;
        Node *left, *right;
    };
    Node *root = nullptr;

    Node *newNode(const T1& k, const T2& v) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->key = k;
        temp->value = v;
        temp->left = temp->right = NULL;
        return temp;
    }

    Node *insertRec(Node *node, const T1& key, const T2& value) {
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
        root = insertRec(root, key, value);
    }

    T2* findRec(Node *node, const T1& key) {
        if (node != NULL) {
            if (key == node->key)
                return &node->value;
            if (key < node->key)
                findRec(node->left, key);
            else
                findRec(node->right, key);
        }
        return NULL;
    }

    T2* find(const T1& key) {
        return find(root, key);
    }

    Node *minValueNode(Node *node) {
        Node *root = node;

        while (root->left != NULL)
            root = root->left;

        return root;
    }

    Node *eraseRec(Node *node, const T1& key) {
        if (node == NULL)
            return node;

        if (key < node->key)
            node->left = eraseRec(node->left, key);
        else if (key > node->key)
            node->right = eraseRec(node->right, key);
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
            node->right = eraseRec(node->right, temp->key);
        }

        return node;
    }

    void erase(const T1& key) {
        root = eraseRec(root, key);
    }
    
    void clearRec(Node* node) {
        if (node == NULL) return;
        clearRec(node->left);
        clearRec(node->right);
        free(node);
    }

    void clear() { 
        clearRec(root);
        root = nullptr;
    }

    T2& operator[](const T1& key) {
        auto res = find(key);
        if (res == nullptr) {
            insert(key, {});
            res = find(key);
        }
        return res;
    }
};