#include <cstdio>

template<typename T>
struct DoublyLinkedList {
    struct Node {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;
    };
    Node* head;

    void clear() {
        Node* curr = head;
        while (head != nullptr) {
            head = head->next;
            delete curr;
            curr = head;
        }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr){
            // if (data == curr->data) return;
            prev = curr;
            curr = curr->next;
        }
        Node* node = new Node{ data, prev, curr };
        if (prev == nullptr) head = node;
        else prev->next = node;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return;
        if (prev == nullptr) {
            head = curr->next;
            curr->prev = nullptr;
        }
        else {
            prev->next = curr->next;
            curr->next->prev = prev;
        }
        delete curr;
    }
    void print() {
        printf(">> head->");
        Node* curr = head;
        while (curr != nullptr) {
            printf("%d<->", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
};

DoublyLinkedList<int> dll;

int main()
{
    dll.insert(10);
    dll.insert(20);
    dll.insert(30);
    dll.insert(20);
    dll.print();

    dll.clear();
    dll.print();

    // dll.remove(20);
    // dll.print();

    // dll.remove(10);
    // dll.print();

    // dll.remove(30);
    // dll.print();

    // dll.clear();
    // dll.print();

    return 0;
}