#pragma once 

#include "..\singly_linked_list\linkedlist.h"

template<typename T>
struct Stack: LinkedList<T> {
    void push(const T& data) { push_front(data); }
    void pop() { pop_front(); }
    T top() { return front(); }
};
