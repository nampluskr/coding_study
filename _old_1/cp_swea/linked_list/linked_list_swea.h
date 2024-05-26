#pragma once

/*
1. template<typename T>
2. int -> T, int data -> const T& data
3. _data -> data / _head -> head
4. list_erase(): return ret;
*/

#include<stdio.h>
#include<malloc.h>

#define NULL (0)

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

        node->prev = NULL;
        node->next = NULL;
        node->data = data;

        return node;
    }

    ListNode* list_insert(ListNode* head, ListNode* new_node)
    {
        ListNode* next = head->next;

        head->next = new_node;
        new_node->next = next;
        new_node->prev = head;

        if (next != NULL)
        {
            next->prev = new_node;
        }

        return new_node;
    }

    int list_erase(ListNode* head, const T& data)
    {
        ListNode* it = head->next;
        int ret = 0;

        while (it != NULL)
        {
            if (it->data == data)
            {
                ListNode* prev = it->prev;
                ListNode* next = it->next;
                ListNode* tmp = it;
                it = it->next;

                prev->next = next;
                if (next != NULL)
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

    // User defined method
    ListNode* head = list_create(NULL);     // dummy node
    int cnt = 0;

    void clear() {
         while (head != NULL) {
            ListNode* tmp = head;
            head = head->next;
            free(tmp);
        }
        head = list_create(NULL);
        cnt = 0;
    }
    ListNode* find(const T& data) {
        auto cur = head->next;
        while (cur != NULL) {
            if (cur->data == data) return cur;
            cur = cur->next;
        }
        return NULL;
    }
    void insert(const T& data) {
        ListNode* node = list_create(data);
        list_insert(head, node);
        cnt++;
    }
    int erase(const T& data) { 
        int res = list_erase(head, data);
        cnt -= res;
        return res; }
    bool empty() { return head->next == NULL; } // cnt == 0
    int size() { return cnt; }
};
