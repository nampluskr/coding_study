#pragma once 

#include "..\singly_linked_list\linkedlist.h"

template<typename T>
struct Queue: LinkedList<T> {
    void push(const T& data) { push_back(data); }
    void pop() { pop_front(); }
};
