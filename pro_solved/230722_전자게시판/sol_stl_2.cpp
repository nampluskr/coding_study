#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

#define MAXL (10)
#define MAX_USERS 10'001
#define MAX_CALLS 50'001
#define DELETED	1

#define MESSAGE	1
#define COMMENT	2
#define REPLY	3

struct User {
	string name;
	int sum_points;

	bool operator<(const User& user) const {
		return (sum_points < user.sum_points) ||
			(sum_points == user.sum_points && name > user.name);
	}
};

unordered_map<string, int> userMap;
vector<User> users;		// 10,000
int userCnt;
unordered_map<int, int> boardMap;
int boardCnt;

struct Message {
	int mID;
	int type;
	int point;
	int sum_points;
	int state;
	int uIdx;
	vector<int> commentList;

	void add(int _uIdx, int _mIdx, int _mPoint) {
		type = MESSAGE;
		point = _mPoint;
		sum_points += _mPoint;
		uIdx = _uIdx;
		users[uIdx].sum_points += _mPoint;
	}
	void del();
};
vector<Message> messages;

struct Comment {
	int type;
	int point;
	int state;
	int uIdx;
	int mIdx;
	vector<int> replyList;

	void add(int _uIdx, int _cIdx, int _mIdx, int _mPoint) {
		type = COMMENT;
		point = _mPoint;
		uIdx = _uIdx;
		mIdx = _mIdx;
		messages[mIdx].commentList.push_back(_cIdx);
		messages[mIdx].sum_points += _mPoint;
		users[uIdx].sum_points += _mPoint;
	}
	void del();
};
vector<Comment> comments;

struct Reply {
	int type;
	int point;
	int state;
	int uIdx;
	int mIdx;
	int cIdx;

	void add(int _uIdx, int _rIdx, int _cIdx, int _mPoint) {
		type = REPLY;
		point = _mPoint;
		uIdx = _uIdx;
		mIdx = comments[_cIdx].mIdx;
		cIdx = _cIdx;
		comments[cIdx].replyList.push_back(_rIdx);
		messages[mIdx].sum_points += _mPoint;
		users[uIdx].sum_points += _mPoint;
	}
	void del();
};
vector<Reply> replies;

void Reply::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		messages[mIdx].sum_points -= point;
		point = 0;
	}
}
void Comment::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		messages[mIdx].sum_points -= point;
		point = 0;
		for (int rIdx : replyList) { replies[rIdx].del(); }
	}
}
void Message::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		sum_points -= point;
		point = 0;
		for (int cIdx : commentList) { comments[cIdx].del(); }
	}
}

struct Data {
	int mID, sum_points;
	bool operator<(const Data& data) const {
		return (sum_points < data.sum_points) ||
			(sum_points == data.sum_points && mID > data.mID);
	}
};

priority_queue<Data> messagePQ;
priority_queue<User> userPQ;

///////////////////////////////////////////////////////////////////
int get_uIdx(string user) {
	int uIdx;
	auto pos = userMap.find(user);
	if (pos == userMap.end()) {
		uIdx = userCnt;
		userMap[user] = uIdx;
		userCnt += 1;
		users[uIdx].name = user;
	}
	else {
		uIdx = pos->second;
	}
	return uIdx;
}
int get_mIdx(int mID) {
	int mIdx;
	auto pos = boardMap.find(mID);
	if (pos == boardMap.end()) {
		mIdx = boardCnt;
		boardMap[mID] = mIdx;
		boardCnt += 1;
	}
	else {
		mIdx = pos->second;
	}
	return mIdx;
}

///////////////////////////////////////////////////////////////////
void init()
{
	userMap.clear();
	users.clear();	users.resize(MAX_USERS);
	userCnt = 0;

	boardMap.clear();
	boardCnt = 0;
	messages.clear();	messages.resize(MAX_CALLS);
	comments.clear();	comments.resize(MAX_CALLS);
	replies.clear();	replies.resize(MAX_CALLS);
}

int writeMessage(char mUser[], int mID, int mPoint)
{
	int uIdx = get_uIdx(string(mUser));
	int mIdx = get_mIdx(mID);

	messages[mIdx].add(uIdx, mIdx, mPoint);
	messages[mIdx].mID = mID;

	userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
	messagePQ.push({ mID, messages[mIdx].sum_points });

	int ret = users[uIdx].sum_points;
	return ret;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
	int uIdx = get_uIdx(string(mUser));
	int mIdx = get_mIdx(mID);
	int targetIdx = get_mIdx(mTargetID);
	int ret;

	if (messages[targetIdx].type == MESSAGE) {
		comments[mIdx].add(uIdx, mIdx, targetIdx, mPoint);

		userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
		messagePQ.push({ mTargetID, messages[targetIdx].sum_points });

		ret = messages[targetIdx].sum_points;
	}
	else if (comments[targetIdx].type == COMMENT) {
		replies[mIdx].add(uIdx, mIdx, targetIdx, mPoint);

		userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
		messagePQ.push({ messages[comments[targetIdx].mIdx].mID, messages[comments[targetIdx].mIdx].sum_points });

		ret = messages[comments[targetIdx].mIdx].sum_points;
	}
	return ret;
}

int erase(int mID)
{
	int mIdx = get_mIdx(mID);
	int ret;
	int uIdx;

	if (messages[mIdx].type == MESSAGE) {
		messages[mIdx].del();
		uIdx = messages[mIdx].uIdx;

		userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
		messagePQ.push({ mID, messages[mIdx].sum_points });

		ret = users[uIdx].sum_points;
	}
	else if (comments[mIdx].type == COMMENT) {
		comments[mIdx].del();
		uIdx = comments[mIdx].uIdx;

		userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
		messagePQ.push({ messages[comments[mIdx].mIdx].mID, messages[comments[mIdx].mIdx].sum_points });

		ret = messages[comments[mIdx].mIdx].sum_points;
	}
	else if (replies[mIdx].type == REPLY) {
		replies[mIdx].del();
		uIdx = replies[mIdx].uIdx;

		userPQ.push({ users[uIdx].name, users[uIdx].sum_points });
		messagePQ.push({ messages[replies[mIdx].mIdx].mID, messages[replies[mIdx].mIdx].sum_points });

		ret = messages[replies[mIdx].mIdx].sum_points;
	}
	return ret;
}

void getBestMessages(int mBestMessageList[])
{
	vector<Data> popped;
	int cnt = 5;
	auto& Q = messagePQ;

	while (!Q.empty() && cnt < 5) {
		Data data = Q.top(); Q.pop();

		if (messages[data.mID].sum_points != data.sum_points) continue;

		popped.push_back(data);
		if (messages[data.mID].state != DELETED) {
			mBestMessageList[cnt] = messages[data.mID].mID;
			cnt += 1;
		}
	}
	for (const auto& data : popped) { Q.push(data); }
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
	vector<User> popped;
	int cnt = 5;
	auto& Q = userPQ;

	while (!Q.empty() && cnt < 5) {
		User user = Q.top(); Q.pop();
		int uIdx = get_uIdx(user.name);

		if (users[uIdx].sum_points != user.sum_points) continue;

		popped.push_back(user);
		strcpy(mBestUserList[cnt], user.name.c_str());
		cnt += 1;
	}
	for (const auto& user : popped) { Q.push(user); }
}
#endif