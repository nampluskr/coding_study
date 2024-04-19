#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

#define NULL (0)

template<typename T>
struct LinkedListRef {
    struct ListNode {
        T data;
        ListNode* prev;
        ListNode* next;
    };
    ListNode* head = NULL;

    ListNode* list_create(const T& _data)
    {
        ListNode* node = (ListNode*)malloc(sizeof(ListNode));
        node->prev = NULL;
        node->next = NULL;
        node->data = _data;
        return node;
    }
    ListNode* list_insert(ListNode* _head, ListNode* new_node)
    {
        ListNode* next = _head->next;
        _head->next = new_node;
        new_node->next = next;
        new_node->prev = _head;

        if (next != NULL)
        {
            next->prev = new_node;
        }
        return new_node;
    }

    int list_erase(ListNode* head, const T& _data)
    {
        ListNode* it = head->next;
        int ret = 0;

        while (it != NULL)
        {
            if (it->data == _data)
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
            }
            else
            {
                it = it->next;
            }
        }
        return ret;
    }

    // =========================================================
    LinkedListRef() { init(); }
    ~LinkedListRef() { clear(); }

    void init() {
        head = list_create(NULL);
    }
    void insert(const T& data) {
        ListNode* node = list_create(data);
        list_insert(head, node);
    }
    void remove(const T& data) {
        int num = list_erase(head, data);
        printf("- Number of nodes deleted: %d\n", num);

    }
    void clear() {
        while (head != NULL) {
            ListNode* tmp = head;
            head = head->next;
            free(tmp);
        }
        init();
    }
    void print() {
        ListNode* it = head;
        printf(">> head -> ");
        while (it != NULL) {
            printf("%d <=> ", it->data);
            it = it->next;
        }
        printf("NULL\n");
    }
};

LinkedListRef<int> L;

int main(int argc, char* argv[])
{
    L.clear();      L.print();

    printf("\n==== [Insert] ====\n");
    L.init();       L.print();
    L.insert(20);   L.print();
    L.insert(10);   L.print();
    L.insert(20);   L.print();
    L.insert(30);   L.print();
    L.insert(20);   L.print();

    printf("\n==== [Remove] ====\n");
    L.remove(20);   L.print();
    L.remove(10);   L.print();
    L.remove(50);   L.print();


    printf("\n==== [Clear] ====\n");
    L.clear();  L.print();

    return 0;
}
#endif