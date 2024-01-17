#if 1
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_POINTS      20000   // addSample() �Լ��� ȣ�� Ƚ�� 20,000 ����
#define MAX_CATEGORIES  11      // �ڷ��� ���� (1 �� mC �� 10)
#define MAX_SIZE        4001    // �ڷ��� x��, y�� ��ġ (1 �� mX, mY �� 4,000)
#define DELETED         1

#define bSize       100     // ���� ��Ƽ�� ũ��
#define bCnt        200     // ��Ƽ�� ��ü ����

struct Points {
    int mX, mY, mC, state;
    int dist(int mX, int mY) { return abs(this->mX - mX) + abs(this->mY - mY); }
};

struct PointData {
    int dist, mX, mY, pIdx;
    bool operator<(const PointData& point) const {
        return (dist > point.dist) || (dist == point.dist && mX > point.mX) ||
               (dist == point.dist && mX == point.mX && mY > point.mY);
    }
};

Points points[MAX_POINTS];
int pointCnt;
unordered_map<int, int> pointMap;
vector<int> pointList[bCnt][bCnt];

int K;        // ���� �̿� ����
int L;        // �ƿ����̾� ����

int get_sampleIndex(int mID) {
    int pIdx;
    auto ptr = pointMap.find(mID);
    if (ptr == pointMap.end()) {
        pIdx = pointCnt++;
        pointMap.emplace(mID, pIdx);
    }
    else { pIdx = ptr->second; }
    return pIdx;
}

////////////////////////////////////////////////////////////////////
void init(int _K, int _L)
{
    K = _K;
    L = _L;
    for (int i = 0; i < MAX_POINTS; i++) { points[i] = {}; }
    pointCnt = 0;
    pointMap.clear();

    for (int i = 0; i < bCnt; i++)
        for (int j = 0; j < bCnt; j++)
            pointList[i][j].clear();
}

void addSample(int mID, int mX, int mY, int mC)
{
    int pIdx = get_sampleIndex(mID);
    points[pIdx] = { mX, mY, mC };                                  // ��ü Ž��
    pointList[(mX - 1) / bSize][(mY - 1) / bSize].push_back(pIdx);  // �κ� Ž��
}

void deleteSample(int mID)
{
    int pIdx = get_sampleIndex(mID);
    points[pIdx].state = DELETED;
}

int predict(int mX, int mY)
{
    priority_queue<PointData> Q;

    // ��ü Ž�� + ������
    //for (int pIdx = 0; pIdx < pointCnt; pIdx++) {
    //    if (points[pIdx].state == DELETED) continue;
    //    Q.push({ points[pIdx].dist(mX, mY), points[pIdx].mX, points[xIdx].mY, pIdx });
    //}

    // �κ� Ž�� + ������
    int sbX = max((mX - 1 - L) / bSize, 0);         // the first bucket index in X
    int sbY = max((mY - 1 - L) / bSize, 0);         // the first bucket index in Y
    int ebX = min((mX - 1 + L) / bSize, bCnt - 1);  // the last bucket index in X
    int ebY = min((mY - 1 + L) / bSize, bCnt - 1);  // the last bucket index in Y

    for (int i = sbX; i <= ebX; i++)
        for (int j = sbY; j <= ebY; j++)
            for (int pIdx : pointList[i][j]) {
                if (points[pIdx].state == DELETED) continue;
                Q.push({ points[pIdx].dist(mX, mY), points[pIdx].mX, points[pIdx].mY, pIdx });
            }

    // KNN ����
    int cnt = 0;
    int topk[MAX_CATEGORIES] = {};
    while (!Q.empty() and cnt < K) {
        auto point = Q.top(); Q.pop();
        if (point.dist > L) { return -1; }
        topk[points[point.pIdx].mC] += 1;
        cnt += 1;
    }

    // ���� ����
    int ret = 1;
    for (int mC = 2; mC < MAX_CATEGORIES; mC++) {
        if (topk[mC] > topk[ret]) { ret = mC; }
        else if (topk[mC] == topk[ret] && mC < ret) { ret = mC; }
    }
    return ret;
}
#endif