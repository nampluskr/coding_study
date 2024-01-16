#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;

#define MAXL            (10)
#define MAX_USERS       10000
#define MAX_MESSAGES    50000

#define ADDED   0
#define REMOVED 1

struct User {
    char mUser[MAXL];
    int totalPoint;

    bool operator<(const User& user) const {
        return (totalPoint < user.totalPoint) ||
               (totalPoint == user.totalPoint && strcmp(mUser, user.mUser) > 0);
    }
};
User users[MAX_USERS];
int userCnt;
unordered_map<string, int> userMap;

struct Message {
    int mID;
    int totalPoint;

    int uIdx;
    int mPoint;
    int parent;
    vector<int> childList;
    int depth;
    int state;

    bool operator <(const Message& msg) const {
        return (totalPoint < msg.totalPoint) ||
            (totalPoint == msg.totalPoint && mID > msg.mID);
    }
};
Message msg[MAX_MESSAGES];
int msgCnt;
unordered_map<int, int> msgMap;
bool visited[MAX_MESSAGES];

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
    users[uIdx].totalPoint += mPoint;

    // message
    msg[mIdx].mID = mID;
    msg[mIdx].totalPoint += mPoint;
    msg[mIdx].uIdx = uIdx;
    msg[mIdx].mPoint = mPoint;
    msg[mIdx].parent = -1;
    msg[mIdx].depth = 0;

    int res = users[uIdx].totalPoint;
    return res;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_msgIndex(mID);
    int tIdx = get_msgIndex(mTargetID);

    // user
    strcpy(users[uIdx].mUser, mUser);
    users[uIdx].totalPoint += mPoint;

    // target = message or comment
    msg[mIdx].mID = mID;
    msg[mIdx].totalPoint += mPoint;
    msg[mIdx].uIdx = uIdx;
    msg[mIdx].mPoint = mPoint;
    msg[mIdx].parent = tIdx;
    msg[mIdx].depth = msg[tIdx].depth + 1;

    msg[tIdx].totalPoint += mPoint;
    msg[tIdx].childList.push_back(mIdx);

    int res;
    if (msg[tIdx].depth == 0) {         // message <- comment
        res = msg[tIdx].totalPoint;
    }
    else if (msg[tIdx].depth == 1) {    // comment <- reply
        msg[msg[tIdx].parent].totalPoint += mPoint;
        res = msg[msg[tIdx].parent].totalPoint;
    }
    return res;
}

void updateDown(int cur) {
    for (int child : msg[cur].childList) {
        if (!visited[child] && msg[child].state != REMOVED) {
            visited[child] = true;
            msg[child].state = REMOVED;
            users[msg[child].uIdx].totalPoint -= msg[child].mPoint;
            msg[cur].totalPoint -= msg[child].mPoint;

            updateDown(child);
        }
    }
}

void updateUP(int cur) {
    int parent = msg[cur].parent;
    while (parent != -1) {
        msg[parent].totalPoint -= msg[cur].totalPoint;
        cur = parent;
        parent = msg[cur].parent;
    }
}

int erase(int mID)
{
    int mIdx = get_msgIndex(mID);
    for (int i = 0; i < msgCnt; i++) { visited[i] = false; }
    visited[mIdx] = true;
    msg[mIdx].state = REMOVED;
    users[msg[mIdx].uIdx].totalPoint -= msg[mIdx].mPoint;

    updateUP(mIdx);
    updateDown(mIdx);

    int res;
    if (msg[mIdx].depth == 0) { res = users[msg[mIdx].uIdx].totalPoint; }
    else if (msg[mIdx].depth == 1) { res = msg[msg[mIdx].parent].totalPoint; }
    else { res = msg[msg[msg[mIdx].parent].parent].totalPoint; }
    return res;
}

void getBestMessages(int mBestMessageList[])
{

}

void getBestUsers(char mBestUserList[][MAXL + 1])
{

}
#endif