// Heapify: O(N), Heap pop: O(KlogN)
#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "heap.h"
#include <vector>
//#include <queue>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;

#define MAXL            (10)
#define MAX_USERS       10000
#define MAX_MESSAGES    50000
#define ERASED 1

struct User {
    char mUser[MAXL + 1];
    int totPoint;

    bool operator<(const User& user) const {
        return (totPoint < user.totPoint) ||
            (totPoint == user.totPoint && strcmp(mUser, user.mUser) > 0);
    }
};
User users[MAX_USERS];
int userCnt;
unordered_map<string, int> userMap;

struct Message {
    int mID;
    int totPoint;
    int mPoint;

    int user;
    int root;
    vector<int> childList;
    int state;
};
Message msg[MAX_MESSAGES];
int msgCnt;
unordered_map<int, int> msgMap;
bool visited[MAX_MESSAGES];

struct MessageData {
    int mID, totPoint;

    bool operator <(const MessageData& msg) const {
        return (totPoint < msg.totPoint) ||
            (totPoint == msg.totPoint && mID > msg.mID);
    }
};

/////////////////////////////////////////////////////////////////////
int get_userIndex(string mUser) {
    int uIdx;
    auto iter = userMap.find(mUser);
    if (iter == userMap.end()) {
        uIdx = userCnt++;
        userMap.emplace(mUser, uIdx);
    }
    else { uIdx = iter->second; }
    return uIdx;
}

int get_msgIndex(int mID) {
    int mIdx;
    auto iter = msgMap.find(mID);
    if (iter == msgMap.end()) {
        mIdx = msgCnt++;
        msgMap.emplace(mID, mIdx);
    }
    else { mIdx = iter->second; }
    return mIdx;
}

/////////////////////////////////////////////////////////////////////
void init()
{
    for (int i = 0; i < MAX_USERS; i++) { users[i] = {}; }
    userCnt = 0;
    userMap.clear();

    for (int i = 0; i < MAX_MESSAGES; i++) { msg[i] = {}; }
    msgCnt = 0;
    msgMap.clear();
}

int writeMessage(char mUser[], int mID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_msgIndex(mID);

    // user
    strcpy(users[uIdx].mUser, mUser);
    users[uIdx].totPoint += mPoint;

    // message
    msg[mIdx].mID = mID;
    msg[mIdx].totPoint += mPoint;
    msg[mIdx].mPoint = mPoint;
    msg[mIdx].user = uIdx;
    msg[mIdx].root = mIdx;

    return users[uIdx].totPoint;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_msgIndex(mID);
    int tIdx = get_msgIndex(mTargetID);

    // user
    strcpy(users[uIdx].mUser, mUser);
    users[uIdx].totPoint += mPoint;

    // comment or reply
    msg[mIdx].mID = mID;
    msg[mIdx].totPoint += mPoint;
    msg[mIdx].mPoint = mPoint;
    msg[mIdx].user = uIdx;
    msg[mIdx].root = msg[tIdx].root;

    // parent and root
    msg[tIdx].childList.push_back(mIdx);
    msg[msg[mIdx].root].totPoint += mPoint;

    return msg[msg[mIdx].root].totPoint;
}

void dfs(int cur) {
    visited[cur] = true;
    msg[cur].state = ERASED;
    users[msg[cur].user].totPoint -= msg[cur].mPoint;
    msg[msg[cur].root].totPoint -= msg[cur].mPoint;

    for (int child : msg[cur].childList)
        if (!visited[child] && msg[child].state != ERASED)
            dfs(child);
}

int erase(int mID)
{
    for (int i = 0; i < msgCnt; i++) { visited[i] = false; }
    int mIdx = get_msgIndex(mID);
    dfs(mIdx);

    if (mIdx == msg[mIdx].root)
        return users[msg[mIdx].user].totPoint;
    else
        return msg[msg[mIdx].root].totPoint;
}

void getBestMessages(int mBestMessageList[])
{
    //priority_queue<MessageData> Q;
    MaxHeap<MessageData, MAX_MESSAGES> Q;
    for (int i = 0; i < msgCnt; i++) {
        if (msg[i].state == ERASED) continue;
        if (i != msg[i].root) continue;
        //Q.push({ msg[i].mID, msg[i].totPoint });
        Q.heap[++Q.cnt] = { msg[i].mID, msg[i].totPoint };
    }
    Q.heapify();

    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto cur = Q.top(); Q.pop();
        mBestMessageList[cnt++] = cur.mID;
    }
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
    //priority_queue<User> Q;
    MaxHeap<User, MAX_USERS> Q;
    for (int i = 0; i < userCnt; i++) {
        //Q.push(users[i]);
        Q.heap[++Q.cnt] = users[i];
    }
    Q.heapify();

    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto cur = Q.top(); Q.pop();
        strcpy(mBestUserList[cnt++], cur.mUser);
    }
}
#endif