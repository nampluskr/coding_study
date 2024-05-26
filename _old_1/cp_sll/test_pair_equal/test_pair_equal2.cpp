#if 0
#include <cstdio>

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr ) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    Node* find(const T& data) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

};

template<typename T1, typename T2>
struct Pair {
    T1 key;
    T2 value;
    bool operator==(const Pair& pair) const { return key == pair.key; }
};

struct Data {
    int number, id;
    bool operator==(const Data& data) const { return number == data.number && id == data.id; }
};

LinkedList<Pair<Data, int>> li;


int main()
{
    li.push_back({ {10, 1}, 1111 });
    li.push_back({ {20, 2}, 2222 });
    li.push_back({ {30, 3}, 3333 });

    auto res1 = li.find({ {30, 3}, 3333 });
    auto res2 = li.find({ {30, 3}, 4444 });
    auto res3 = li.find({ {30, 2}, 3333 });

    return 0;
}
#endif