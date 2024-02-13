#if 0
// set 1826 ms / pq-1: 1101 ms / pq-2: 713 ms
#include <vector>
#include <set>
using namespace std;

#define MAX_PLAYERS 39'990
#define MAX_LEAGUES 3'999

struct Player {
    int ID, ability;

    bool operator<(const Player& player) const {
        return (ability < player.ability) || (ability == player.ability && ID > player.ID);
    }
};
//Player players[MAX_PLAYERS];
int N;      // # of players
int L;      // # of leagues

struct League {
    set<Player> playerList;

    void clear() {
        playerList.clear();
    }
    void push(const Player& player) {
        playerList.insert(player);
    }
    Player getMax() {
        auto iter = --playerList.end();
        auto player = *iter;
        playerList.erase(iter);
        return player;
    }
    Player getMin() {
        auto iter = playerList.begin();
        auto player = *iter;
        playerList.erase(iter);
        return player;
    }
    Player getMedian() {
        auto iter = playerList.begin();
        advance(iter, (N / L) / 2);
        auto player = *iter;
        playerList.erase(iter);
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
        leagues[i] = {};
        //leagues[i].clear();
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