// Heap pop: O(3logN)
#if 0
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

priority_queue<Author> authorPQ;
priority_queue<BookData> bookPQ[MAX_CATEGORIES];

/////////////////////////////////////////////////////////////////////
void init(int N, int C)
{
    for (int i = 0; i < MAX_BOOKS; i++) { books[i] = {}; }

    while (!authorPQ.empty()) { authorPQ.pop(); }
    for (int i = 1; i <= N; i++) { 
        authors[i] = { i, 0 };
        authorPQ.push({ i, 0 });
    }
    for (int i = 0; i <= C; i++) { 
        bookList[i] = {}; 
        bookCnt[i] = 0;
        while (!bookPQ[i].empty()) { bookPQ[i].pop(); }
    }
    authorCnt = N;
}

void addBookInfo(int bID, int cID, int price, int num, int aIDs[])
{
    books[bID] = { bID, cID, price, num };
    books[bID].stock += 1;

    for (int i = 0; i < num; i++) {
        books[bID].aIDs.push_back(aIDs[i]);
    }
    bookList[cID].push_back({ bID, 0 });
    bookList[0].push_back({ bID, 0 });

    bookPQ[cID].push({bID, 0});
    bookPQ[0].push({bID, 0});

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
        bookPQ[books[bID].cID].push({ bID, books[bID].sales });
        bookPQ[0].push({ bID, books[bID].sales });

        for (int aID : books[bID].aIDs) {
            authors[aID].income += books[bID].price * cnt / books[bID].num;
            authorPQ.push({ aID, authors[aID].income });
        }
    }
    return res;
}

int getBestSeller(int cID, int bIDs[])
{
    auto& Q = bookPQ;
    int cnt = 0;
    vector<int> popped;
    while (!Q[cID].empty() && cnt < 3) {
        auto cur = Q[cID].top(); Q[cID].pop();

        if (books[cur.bID].state == REMOVED) continue;
        if (books[cur.bID].sales != cur.sales) continue;
        bIDs[cnt++] = cur.bID;
        popped.push_back(cur.bID);
    }
    for (int bID : popped) { Q[cID].push({ bID, books[bID].sales }); }
    return min(bookCnt[cID], 3);
}

void getBestAuthors(int aIDs[])
{
    auto& Q = authorPQ;
    int cnt = 0;
    vector<int> popped;
    while (!Q.empty() && cnt < 3) {
        auto cur = Q.top(); Q.pop();

        if (authors[cur.aID].income != cur.income) continue;
        aIDs[cnt++] = cur.aID;
        popped.push_back(cur.aID);
    }
    for (int aID : popped) { Q.push({ aID, authors[aID].income }); }
}
#endif