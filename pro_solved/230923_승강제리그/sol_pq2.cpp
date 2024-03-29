#if 1
// set 1826 ms / pq-1: 1101 ms / pq-2: 713 ms
#include <vector>
#include <queue>
using namespace std;

#define MAX_PLAYERS 39'990
#define MAX_LEAGUES 3'999

struct Player {
    int ID, ability, league;

    bool operator<(const Player& player) const {
        return (ability < player.ability) || (ability == player.ability && ID > player.ID);
    }
    bool operator>(const Player& player) const {
        return (ability > player.ability) || (ability == player.ability && ID < player.ID);
    }
    bool operator==(const Player& player) const {
        return ability == player.ability && ID == player.ID;
    }
};
Player players[MAX_PLAYERS];
int N;      // # of players
int L;      // # of leagues

struct League {
    priority_queue<Player, vector<Player>, less<Player>> maxHeap;       // max
    priority_queue<Player, vector<Player>, greater<Player>> minHeap;    // min
    priority_queue<Player, vector<Player>, less<Player>> leftHeap;      // x < median
    priority_queue<Player, vector<Player>, greater<Player>> rightHeap;  // x > median

    int league;
    int leftSize, rightSize;

    template<typename Heap>
    Player getTop(Heap& Q) {
        //remove popped players (TC = 2)
        while (!Q.empty() && players[Q.top().ID].league != league) { Q.pop(); }

        auto player = Q.top(); Q.pop();

        //remove duplicate players (TC = 1)
        while (!Q.empty() && player == Q.top()) { Q.pop(); }
        return player;
    }
    void push(const Player& player) {
        players[player.ID].league = league;
        maxHeap.push(player);
        minHeap.push(player);

        if (leftSize == rightSize) {
            rightHeap.push(player);
            auto player = getTop(rightHeap);
            leftHeap.push(player);
            leftSize++;
        }
        else if (leftSize > rightSize) {
            leftHeap.push(player);
            auto player = getTop(leftHeap);
            rightHeap.push(player);
            rightSize++;
        }
    }
    Player getMin() {
        auto player = getTop(minHeap);
        leftSize -= 1;
        return player;
    }
    Player getMax() {
        auto player = getTop(maxHeap);
        rightSize -= 1;
        return player;
    }
    Player getMedian() {
        Player player = {};
        if (leftSize == rightSize) {
            player = getTop(rightHeap);
            rightSize--;
        }
        else if (leftSize > rightSize) {
            player = getTop(leftHeap);
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
void init(int _N, int _L, int ability[])
{
    N = _N;
    L = _L;
    for (int i = 0; i < L; i++) {
        leagues[i] = {};
        leagues[i].league = i;
    }
    for (int i = 0; i < N; i++) {
        players[i] = { i, ability[i], i / (N / L) };
        leagues[i / (N / L)].push(players[i]);
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