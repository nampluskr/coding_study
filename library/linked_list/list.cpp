#include "list.h"
#include <cstdio>

List<int> L;
Stack<int> S;
Queue<int> Q;

template<typename T>
void print(const T& list) {
	for (auto ptr = list.head; ptr; ptr = ptr->next)
		printf("[%d]->", ptr->data);
	printf("->null\n");
}

void test_list() {
	L.clear();
	L.push_front(1);
	L.push_front(2);
	L.push_front(3);
	L.push_front(4);
	print(L);

	L.clear();
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	print(L);
}

void test_stack() {
	S.clear();
	S.push(1);
	S.push(2);
	S.push(3);
	S.push(4);
	print(S);

	while (!S.empty()) {
		int data = S.top(); S.pop();
		printf(">> popped: %d\n", data);
	}
	print(S);
}

void test_queue() {
	Q.clear();
	Q.push(1);
	Q.push(2);
	Q.push(3);
	Q.push(4);
	print(Q);

	while (!Q.empty()) {
		int data = Q.front(); Q.pop();
		printf(">> popped: %d\n", data);
	}
	print(Q);
}