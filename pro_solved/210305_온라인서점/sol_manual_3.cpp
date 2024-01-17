// Heapify: O(N) / Heap pop: O(3logN)
#if 0
#include "heap.h"
#include <vector>
#include <queue>
using namespace std;

#define MAX_BOOKS       (100000 + 1)
#define MAX_AUTHORS     (10000 + 1)
#define MAX_CATEGORIES  (20 + 1)
#define REMOVED         1

struct Book {
    int bID, cID, price, num;
    vector<int> aIDs;
    int sales;
    int stock;
    int state;
};
Book books[MAX_BOOKS];

struct Author {
    int aID, income;
    bool operator<(const Author& author) const {
        return (income < author.income) || (income == author.income && aID > author.aID);
    }
};
Author authors[MAX_AUTHORS];
int authorCnt;

struct BookData {
    int bID, sales;
    bool operator<(const BookData& book) const {
        return (sales < book.sales) || (sales == book.sales && bID < book.bID);
    }
};
vector<BookData> bookList[MAX_CATEGORIES];
int bookCnt[MAX_CATEGORIES];

/////////////////////////////////////////////////////////////////////
void init(int N, int C)
{
    for (int i = 0; i < MAX_BOOKS; i++) { books[i] = {}; }
    for (int i = 1; i <= N; i++) { authors[i] = { i, 0 }; }
    for (int i = 0; i <= C; i++) { bookList[i] = {}; bookCnt[i] = 0; }
    authorCnt = N;
}

void addBookInfo(int bID, int cID, int price, int num, int aIDs[])
{
    books[bID] = { bID, cID, price, num };
    books[bID].stock += 1;

    for (int i = 0; i < num; i++) {
        books[bID].aIDs.push_back(aIDs[i]);
    }
    bookList[cID].push_back({ bID, books[bID].sales });
    bookList[0].push_back({ bID, books[bID].sales });

    bookCnt[cID]++;
    bookCnt[0]++;
}

void addBookStock(int bID, int cnt)
{
    books[bID].stock += cnt;
}

void removeBookInfo(int bID)
{
    books[bID].state = REMOVED;
    bookCnt[books[bID].cID]--;
    bookCnt[0]--;
}

int sellBooks(int bID, int cnt)
{
    int res = 0;
    if (books[bID].stock >= cnt) {
        res = 1;
        books[bID].stock -= cnt;
        books[bID].sales += cnt;
        for (int aID : books[bID].aIDs) {
            authors[aID].income += books[bID].price * cnt / books[bID].num;
        }
    }
    return res;
}

int getBestSeller(int cID, int bIDs[])
{
    MaxHeap<BookData, MAX_BOOKS> Q;
    for (auto book : bookList[cID]) {
        if (books[book.bID].state != REMOVED) {
            //Q.push({ book.bID, books[book.bID].sales });
            Q.cnt++;
            Q.heap[Q.cnt] = { book.bID, books[book.bID].sales };
        }
    }
    Q.heapify();

    int cnt = 0;
    while (!Q.empty() && cnt < 3) {
        auto cur = Q.top(); Q.pop();
        bIDs[cnt++] = cur.bID;
    }
    return min(bookCnt[cID], 3);
}

void getBestAuthors(int aIDs[])
{
    MaxHeap<Author, MAX_AUTHORS> Q;
    for (int aID = 1; aID <= authorCnt; aID++) {
        //Q.push(authors[aID]);
        Q.heap[++Q.cnt] = authors[aID];
    }
    Q.heapify();

    int cnt = 0;
    while (!Q.empty() && cnt < 3) {
        auto cur = Q.top(); Q.pop();
        aIDs[cnt++] = cur.aID;
    }
}
#endif