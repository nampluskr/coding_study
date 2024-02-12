#if 0
// [STL prioirty_queue] 1034 ms (WS)
#include <vector>
#include <queue>
using namespace std;

#define MAX_PLAYERS 39990
#define MAX_LEAGUES 3999

struct Player {
    int ID;
    int ability;
    int league;

    bool operator<(const Player& p) const {
        return (ability < p.ability) || (ability == p.ability && ID > p.ID);
    }
    bool operator>(const Player& p) const {
        return (ability > p.ability) || (ability == p.ability && ID < p.ID);
    }
};
Player players[MAX_PLAYERS];
int playerCnt;

struct League {
    priority_queue<Player, vector<Player>, less<Player>> maxHeap;       // max
    priority_queue<Player, vector<Player>, greater<Player>> minHeap;    // min
    priority_queue<Player, vector<Player>, less<Player>> leftHeap;      // x < middle
    priority_queue<Player, vector<Player>, greater<Player>> rightHeap;  // x > middle

    int league;
    Player middle;
    int leftSize = 0, rightSize = 0, totalSize = 0;
    template<typename Heap>
    void refresh(Heap& Q) {
        while (!Q.empty()) Q.pop();
    }
    bool isMember(const Player& player) { return players[player.ID].league == league; }
    void push(const Player& player) {
        totalSize += 1;
        players[player.ID].league = league;

        // 최대값 (maxHeap), 최소값 (minHeap)
        maxHeap.push(player);
        minHeap.push(player);

        // 중앙값 (leftHeap - middle - rightHeap)
        //if (totalSize == 1) { middle = player;  return; }
        if (totalSize == 1 && leftSize == 0 && rightSize == 0) { middle = player; return; }

        // player == middle 이면 추가하지 않음 (TC = 1)
        if (player < middle) { leftHeap.push(player); leftSize += 1; }
        else if (player > middle) { rightHeap.push(player); rightSize += 1; }

        // leftSize == rightSize 동일하게 맞춘다. (차이가 2일때)
        if (leftSize == rightSize || totalSize % 2 == 0) { return; }
        else if (leftSize > rightSize) {
            rightHeap.push(middle);
            middle = leftHeap.top(); leftHeap.pop();
            rightSize += 1;
            leftSize -= 1;
        }
        else if (leftSize < rightSize) {
            leftHeap.push(middle);
            middle = rightHeap.top(); rightHeap.pop();
            leftSize += 1;
            rightSize -= 1;
        }
    }
    Player getMin() {
        //while (!minHeap.empty() && !isMember(minHeap.top())) { minHeap.pop(); }
        auto player = minHeap.top(); minHeap.pop();
        leftSize -= 1;
        totalSize -= 1;
        return player;
    }
    Player getMax() {
        //while (!maxHeap.empty() && !isMember(maxHeap.top())) { maxHeap.pop(); }
        auto player = maxHeap.top(); maxHeap.pop();
        rightSize -= 1;
        totalSize -= 1;
        return player;
    }
    Player getMedian() {
        totalSize -= 1;
        //while (!leftHeap.empty() && !isMember(leftHeap.top())) { leftHeap.pop(); }
        //while (!rightHeap.empty() && !isMember(rightHeap.top())) { rightHeap.pop(); }

        // middle 값이 이전에 pop 되어 다른 리그로 변경되었다면 (TC = 2)
        while (!isMember(middle)) {
            if (leftSize >= rightSize) { middle = leftHeap.top(); leftHeap.pop(); }
            else { middle = rightHeap.top(); rightHeap.pop(); }
        }

        auto player = middle;
        if (leftSize >= rightSize) {
            middle = leftHeap.top(); leftHeap.pop();
            leftSize -= 1;
        }
        else {
            middle = rightHeap.top(); rightHeap.pop();
            rightSize -= 1;
        }
        return player;
    }
};
League leagues[MAX_LEAGUES];
int leagueCnt;

Player maxIDList[MAX_LEAGUES];
Player minIDList[MAX_LEAGUES];
Player midIDList[MAX_LEAGUES];


/////////////////////////////////////////////////////////////////////
void init(int N, int L, int ability[])
{
    playerCnt = N;
    for (int i = 0; i < N; i++) { players[i] = {}; }

    leagueCnt = L;
    for (int i = 0; i < L; i++) { leagues[i] = {}; }

    for (int i = 0; i < playerCnt; i++) {
        players[i] = { i, ability[i], i / (N / L) };
        leagues[i / (N / L)].league = i / (N / L);
        leagues[i / (N / L)].push(players[i]);
    }
}

int move()
{
    int ret = 0;

    // 상위리그 최대값, 하위리그 최소값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        auto minPlayer = leagues[i].getMin();
        auto maxPlayer = leagues[i + 1].getMax();
        minIDList[i] = minPlayer;
        maxIDList[i] = maxPlayer;
        ret += minPlayer.ID + maxPlayer.ID;
    }

    // 상위리그 - 하위리그 move
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].push(maxIDList[i]);
        leagues[i + 1].push(minIDList[i]);
    }
    return ret;
}

int trade()
{
    int ret = 0;

    // 상위리그 중앙값, 하위리그 최대값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        auto midPlayer = leagues[i].getMedian();
        auto maxPlayer = leagues[i + 1].getMax();
        midIDList[i] = midPlayer;
        maxIDList[i] = maxPlayer;
        ret += midPlayer.ID + maxPlayer.ID;
    }
    // 상위리그 - 하위리그 trade
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].push(maxIDList[i]);
        leagues[i + 1].push(midIDList[i]);
    }
    return ret;
}
#endif