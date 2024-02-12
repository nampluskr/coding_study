#if 0
// Home PC set: 1814 ms
#include <vector>
#include <set>
using namespace std;

#define MAX_PLAYERS 39'990  // N: 선수들의 수(9 ≤ N ≤ 39,990)
#define MAX_LEAGUES 3'999   // L : 리그의 개수(3 ≤ L ≤ 10, 3 ≤ N / L ≤ 3,999)

struct Player {
    int ID, ability;
    bool operator<(const Player& player) const {
        return (ability < player.ability) || 
               (ability == player.ability && ID > player.ID );
    }
};
//Player players[MAX_PLAYERS];
int playerCnt;
int leagueCnt;
int leagueSize;

struct League {
    set<Player> playerList;     // 오름차순

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
        advance(iter, leagueSize / 2);
        auto player = *iter;
        playerList.erase(iter);
        return player;
    }
};
League leagues[MAX_LEAGUES];


/////////////////////////////////////////////////////////////////////
void init(int N, int L, int mAbility[])
{
    playerCnt = N;
    leagueCnt = L;
    leagueSize = N / L;

    //for (int i = 0; i < N; i++) { players[i] = {}; }
    for (int i = 0; i < L; i++) { leagues[i].clear(); }

    for (int i = 0; i < N; i++) { 
        //players[i] = { i, mAbility[i] };
        leagues[i / leagueSize].push({ i, mAbility[i] });
    }
}

// 각 리그 별로 능력이 가장 좋은 선수와 상위 리그의 가장 나쁜 선수를 선발하여 교환하고,
// 전체 리그에서 이동한 선수들의 ID 값의 합을 반환한다.
int move()
{
    vector<Player> maxPlayerList;
    vector<Player> minPlayerList;

    int res = 0;
    for (int i = 0; i < leagueCnt - 1; i++) {
        auto minPlayer = leagues[i].getMin();
        auto maxPlayer = leagues[i + 1].getMax();

        res += minPlayer.ID;
        res += maxPlayer.ID;

        minPlayerList.push_back(minPlayer);
        maxPlayerList.push_back(maxPlayer);
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].push(maxPlayerList[i]);
        leagues[i + 1].push(minPlayerList[i]);
    }
    return res;
}

// 각 리그 별로 능력이 가장 좋은 선수와 상위 리그의 중간급 선수를 선발하여 교환하고, 
// 전체 리그에서 이동한 선수들의 ID 값의 합을 반환한다.
int trade()
{
    vector<Player> maxPlayerList;
    vector<Player> medPlayerList;

    int res = 0;
    for (int i = 0; i < leagueCnt - 1; i++) {
        auto medPlayer = leagues[i].getMedian();
        auto maxPlayer = leagues[i + 1].getMax();

        res += medPlayer.ID;
        res += maxPlayer.ID;

        maxPlayerList.push_back(maxPlayer);
        medPlayerList.push_back(medPlayer);
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].push(maxPlayerList[i]);
        leagues[i + 1].push(medPlayerList[i]);
    }
    return res;
}
#endif