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
#define MAX_USERS       10000   // 사용자의 수는 10,000 이하이다.
#define MAX_MESSAGES    50000   // 모든 함수의 호출 횟수는 50,000 이하이다.

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

    int mPoint;
    int user;
    int root;
    int parent;
    int depth;
    vector<int> childList;
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
    return -1;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    return -1;
}

int erase(int mID)
{
    return -1;
}

void getBestMessages(int mBestMessageList[])
{

}

void getBestUsers(char mBestUserList[][MAXL + 1])
{

}
#endif