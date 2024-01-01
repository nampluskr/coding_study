#include <cstdio>
#include "linked_list_sll.h"

LinkedList<int> L;
Stack<int> S;
Queue<int> Q;

ListArray<int, 10> listArr;
StackArray<int, 10> stackArr;
QueueArray<int, 10> queueArr;

template<typename T>
void print(const T& list) {
    for (auto ptr = list.head; ptr; ptr = ptr->next)
        printf("[%d]->", ptr->data);
    printf("\n");
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = 5;

    //for (int i = 0; i < n; i++) {
    //    S.push(arr[i]);
    //    Q.push(arr[i]);
    //}
    //print(S);
    //print(Q);

    //for (int i = 0; i < n; i++) {
    //    stackArr.push(arr[i]);
    //    queueArr.push(arr[i]);
    //}
    //while (!stackArr.empty()) { stackArr.pop(); }
    //while (!queueArr.empty()) { queueArr.pop(); }

    for (int i = 0; i < n; i++) {
        listArr.push_back(arr[i]);
        //listArr.push_front(arr[i]);
    }
    //while (!listArr.empty()) { listArr.pop_back(); }
    while (!listArr.empty()) { listArr.pop_front(); }


    return 0;
}