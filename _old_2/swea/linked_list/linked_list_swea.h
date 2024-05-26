#pragma once

#include <malloc.h>

template<typename T>
struct LinkedListSWEA {
    struct Node
    {
        T data;
        struct Node* prev;
        struct Node* next;
    };
    Node* head = list_create({});

    Node* list_create(const T& data)
    {
        Node* node = (Node*)malloc(sizeof(Node));

        node->prev = NULL;
        node->next = NULL;
        node->data = data;

        return node;
    }

    Node* list_insert(Node* head, Node* new_node)
    {
        Node* next = head->next;

        head->next = new_node;
        new_node->next = next;
        new_node->prev = head;

        if (next != NULL)
        {
            next->prev = new_node;
        }
        return new_node;
    }

    int list_erase(Node* head, const T& data)
    {
        Node* it = head->next;
        int ret = 0;

        while (it != NULL)
        {
            if (it->data == data)
            {
                Node* prev = it->prev;
                Node* next = it->next;
                Node* tmp = it;
                it = it->next;

                prev->next = next;
                if (next != NULL)
                {
                    next->prev = prev;
                }
                free(tmp);
                ret++;
            }
            else
            {
                it = it->next;
            }
        }
        return ret;
    }

    void clear() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            free(temp);
        }
        head = list_create({});
    }
    void insert(const T& data) { 
        Node* node = list_create(data);
        list_insert(head, node);
    }
    T* find(const T& data) {
        Node* cur = head->next;
        while (cur != NULL) {
            if (cur->data == data) return &cur->data;
            cur = cur->next;
        }
        return NULL;
    }
    void erase(const T& data) {
        list_erase(head, data);
    }
};