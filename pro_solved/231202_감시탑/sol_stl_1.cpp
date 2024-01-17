#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

#define MAX_TOWERS  50000
#define MAX_N       5001    // 평원 한 변의 길이 ( 10 <= N <= 5,000 )
#define MAX_COLORS  (5 + 1) // 0 <= mColor <= 5

#define MAX_BSIZE   70      // sqrt(5001)
#define MAX_BCNT    72      // ceil(5001 / 70)

#define REMOVED     1

struct Tower {
    int mRow, mCol, mColor;
    int state;
};
Tower towers[MAX_TOWERS];
int towerCnt;
unordered_map<int, int> towerMap;

int N;

/////////////////////////////////////////////////////////////////////
int get_towerIndex(int mRow, int mCol) {
    int key = mRow * 10000 + mCol;
    int tIdx;
    auto iter = towerMap.find(key);
    if (iter == towerMap.end()) {
        tIdx = towerCnt++;
        towerMap.emplace(key, tIdx);
    }
    else { tIdx = iter->second; }
    return tIdx;
}

struct Partition2D {
    int idxCnt[MAX_COLORS][MAX_BCNT][MAX_BCNT];
    vector<int> idxList[MAX_COLORS][MAX_BCNT][MAX_BCNT];
    int bSize;          // bucket size
    int bCnt;           // num. of buckets

    int init(int N) {
        bSize = sqrt(N);
        bCnt = ceil((double)N / bSize);

        for (int c = 0; c < MAX_COLORS; c++)
            for (int i = 0; i < bCnt; i++)
                for (int j = 0; j < bCnt; j++){
                    idxCnt[c][i][j] = 0;
                    idxList[c][i][j].clear();
                }
    }
    void update(int mRow, int mCol, int mColor, int diff) {
        int tIdx = get_towerIndex(mRow, mCol);
        int bRow = (mRow - 1) / bSize;
        int bCol = (mCol - 1) / bSize;

        idxCnt[mColor][bRow][bCol] += diff;
        idxCnt[0][bRow][bCol] += diff;

        if (diff > 0) {
            idxList[mColor][bRow][bCol].push_back(tIdx);
            idxList[0][bRow][bCol].push_back(tIdx);
        }
    }
    int query(int mRow, int mCol, int mColor, int mDis) {
        int minR = max(mRow - mDis, 1), maxR = min(mRow + mDis, N);
        int minC = max(mCol - mDis, 1), maxC = min(mCol + mDis, N);
        int bMinR = (minR - 1) / bSize, bMmaxR = (maxR - 1) / bSize;
        int bMinC = (minC - 1) / bSize, bMmaxC = (maxC - 1) / bSize;

    }
    int query(int bRow, int bCol) {
    }
};
Partition2D P;

/////////////////////////////////////////////////////////////////////
void init(int _N)
{
    N = _N;
    for (int i = 0; i < MAX_TOWERS; i++) { towers[i] = {}; }
    towerCnt = 0;
    towerMap.clear();

    P.init(N);
}

void buildTower(int mRow, int mCol, int mColor)
{
    int tIdx = get_towerIndex(mRow, mCol);
    towers[tIdx] = { mRow, mCol, mCol };

    P.update(mRow, mCol, mColor, +1);
}

void removeTower(int mRow, int mCol)
{
    int tIdx = get_towerIndex(mRow, mCol);
    towers[tIdx].state = REMOVED;

    P.update(mRow, mCol, towers[tIdx].mColor, -1);
}

// 1,000
int countTower(int mRow, int mCol, int mColor, int mDis)
{
    return P.query(mRow, mCol, mColor, mDis);
}

// 5,000
int getClosest(int mRow, int mCol, int mColor)
{

    return 0;
}