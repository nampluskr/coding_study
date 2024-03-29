#if 0
// set 1826 ms / pq-1: 1101 ms / pq-2: 713 ms
#include <vector>
#include <queue>
using namespace std;

#define MAX_PLAYERS 39'990
#define MAX_LEAGUES 3'999

struct Player {
    int ID, ability;

    bool operator<(const Player& player) const {
        return (ability < player.ability) || (ability == player.ability && ID > player.ID);
    }
    bool operator>(const Player& player) const {
        return (ability > player.ability) || (ability == player.ability && ID < player.ID);
    }
};
//Player players[MAX_PLAYERS];
int N;      // # of players
int L;      // # of leagues

struct League {
    struct MaxPlayer {
        Player player;
        int idx;
        bool operator<(const MaxPlayer& max) const { return player < max.player; }
    };
    struct MinPlayer {
        Player player;
        int idx;
        bool operator<(const MinPlayer& min) const { return player > min.player; }
    };

    // Min / Max
    priority_queue<MaxPlayer> maxHeap;
    priority_queue<MinPlayer> minHeap;
    vector<bool> popped;
    int idx;

    // Median
    priority_queue<MaxPlayer> leftHeap;
    priority_queue<MinPlayer> rightHeap;
    int leftSize, rightSize;

    void clear() {
        while (!maxHeap.empty()) maxHeap.pop();
        while (!minHeap.empty()) minHeap.pop();
        popped.clear();
        idx = 0;

        // Median
        while (!leftHeap.empty()) leftHeap.pop();
        while (!rightHeap.empty()) rightHeap.pop();
        leftSize = rightSize = 0;
    }
    template<typename Heap>
    void refresh(Heap& Q) {
        while (!Q.empty() && popped[Q.top().idx]) Q.pop();
    }
    void push(const Player& player) {
        maxHeap.push({ player, idx });
        minHeap.push({ player, idx });
        popped.push_back(false);

        if (leftSize == rightSize) {
            rightHeap.push({ player, idx });
            refresh(rightHeap);
            auto top = rightHeap.top(); rightHeap.pop();
            leftHeap.push({ top.player, top.idx });
            leftSize++;
        }
        else if (leftSize > rightSize) {
            leftHeap.push({ player, idx });
            refresh(leftHeap);
            auto top = leftHeap.top(); leftHeap.pop();
            rightHeap.push({ top.player, top.idx });
            rightSize++;
        }
        idx++;
    }
    Player getMin() {
        refresh(minHeap);
        auto top = minHeap.top(); minHeap.pop();
        popped[top.idx] = true;
        leftSize--;
        return top.player;
    }
    Player getMax() {
        refresh(maxHeap);
        auto top = maxHeap.top(); maxHeap.pop();
        popped[top.idx] = true;
        rightSize--;
        return top.player;
    }
    Player getMedian() {
        Player player = {};
        if (leftSize == rightSize) {
            refresh(rightHeap);
            auto top = rightHeap.top(); rightHeap.pop();
            player = top.player;
            popped[top.idx] = true;
            rightSize--;
        }
        else if (leftSize > rightSize) {
            refresh(leftHeap);
            auto top = leftHeap.top(); leftHeap.pop();
            player = top.player;
            popped[top.idx] = true;
            leftSize--;
        }
        return player;
    }
};
League leagues[MAX_LEAGUES];

Player maxPlayerList[MAX_LEAGUES];
Player minPlayerList[MAX_LEAGUES];
Player medPlayerList[MAX_LEAGUES];

/////////////////////////////////////////////////////////////////////
void init(int _N, int _L, int mAbility[])
{
    N = _N;
    L = _L;
    for (int i = 0; i < L; i++) {
        leagues[i] = {};      // 600 ms
        //leagues[i].clear();     // 783 ms
    }
    for (int i = 0; i < N; i++) {
        //players[i] = { i, mAbility[i] };
        leagues[i / (N / L)].push({ i, mAbility[i] });
    }
}

int move()
{
    int res = 0;
    for (int i = 0; i < L - 1; i++) {
        auto minPlayer = leagues[i].getMin();
        auto maxPlayer = leagues[i + 1].getMax();

        minPlayerList[i] = minPlayer;
        maxPlayerList[i] = maxPlayer;

        res += minPlayer.ID + maxPlayer.ID;
    }
    for (int i = 0; i < L - 1; i++) {
        leagues[i].push(maxPlayerList[i]);
        leagues[i + 1].push(minPlayerList[i]);
    }
    return res;
}

int trade()
{
    int res = 0;
    for (int i = 0; i < L - 1; i++) {
        auto medPlayer = leagues[i].getMedian();
        auto maxPlayer = leagues[i + 1].getMax();

        medPlayerList[i] = medPlayer;
        maxPlayerList[i] = maxPlayer;

        res += medPlayer.ID + maxPlayer.ID;
    }
    for (int i = 0; i < L - 1; i++) {
        leagues[i].push(maxPlayerList[i]);
        leagues[i + 1].push(medPlayerList[i]);
    }
    return res;
}
#endif