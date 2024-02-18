#if 0
// 31 s
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_N		(3000 + 1)
#define MAX_HOLES	(30000 + 1)

struct Position {
	int row, col;

	int get_dist(int mRow, int mCol) {
		if (abs(row - mRow) == abs(col - mCol)) return abs(row - mRow) * 14;
		else return abs(row - mRow) * 10 + abs(col - mCol) * 10;
	}
	int get_slope(int mRow, int mCol) {
		return (row - mRow) / (col - mCol);
	}
};

struct Hole {
	Position pos;
	int state;
};
Hole holes[MAX_HOLES];
int holeMap[MAX_N][MAX_N];		// hole ID
int holeMapTemp[MAX_N][MAX_N];	// hole ID
bool visited[MAX_N][MAX_N];

vector<int> holesRow[MAX_N];	// holes ID's
vector<int> holesCol[MAX_N];	// holes ID's
vector<Position> diagonals[MAX_N][MAX_N];

vector<int> holeList;
int N;

struct HoleData {
	int mID, row, col, dist;

	bool operator<(const HoleData& hole) const {
		return (dist > hole.dist) ||
			(dist == hole.dist && row > hole.row) ||
			(dist == hole.dist && row == hole.row && col > hole.col);
	}
};
priority_queue<HoleData> Q;

/////////////////////////////////////////////////////////////////////
void dfs(int mRow, int mCol) {
	visited[mRow][mCol] = true;
	if (holeMapTemp[mRow][mCol] > 0)	// not erased
		holeList.push_back(holeMap[mRow][mCol]);

	for (const auto& next : diagonals[mRow][mCol]){
		if (abs(mRow - next.row) != abs(mCol - next.col)) continue;
		if (!visited[next.row][next.col])
			dfs(next.row, next.col);
	}
}

void bfs(int mRow, int mCol, int slope) {
	queue<Position> Q;

	visited[mRow][mCol] = true;
	Q.push({ mRow, mCol });
	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();

		int mID = holeMapTemp[cur.row][cur.col];
		if (mID > 0) {	// not erased
			holeList.push_back(mID);
			break;
		}

		for (const auto& next : diagonals[cur.row][cur.col]) {
			//if (abs(cur.row - next.row) != abs(cur.col - next.col)) continue;
			if (cur.get_slope(next.row, next.col) != slope) continue;
			if (!visited[next.row][next.col]) {
				visited[next.row][next.col] = true;
				Q.push(next);
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////
void init(int _N)
{
	N = _N;
	for (int i = 0; i < MAX_HOLES; i++) { 
		holes[i] = {};
	}
	for (int i = 1; i <= N; i++) {
		holesRow[i] = {};
		holesCol[i] = {};
		for (int j = 1; j <= N; j++) {
			holeMap[i][j] = 0;
			diagonals[i][j] = {};
		}
	}
	//while (!Q.empty()) { Q.pop(); }
}

void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)
{
	if (mBCol < mACol) { swap(mACol, mBCol); swap(mARow, mBRow); }

	int slope = (mARow < mBRow) ? 1 : -1;
	Position cur = { mARow, mACol };

	for (int col = mACol + 1; col <= mBCol; col++) {
		Position next = { slope * (col - cur.col) + cur.row, col };
		diagonals[cur.row][cur.col].push_back(next);
		diagonals[next.row][next.col].push_back(cur);
		cur = next;
	}
}

// 3,000
void addHole(int mRow, int mCol, int mID)
{
	holes[mID].pos = { mRow, mCol };
	holeMap[mRow][mCol] = mID;
	holesRow[mRow].push_back(mID);
	holesCol[mCol].push_back(mID);
}

// 3,000
void eraseHole(int mRow, int mCol)
{
	holeMap[mRow][mCol] = 0;
}

// 10,000
// mK : 구슬 치기의 반복 횟수 ( 1 ≤ mK ≤ 20 )
int hitMarble(int mRow, int mCol, int mK)
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			holeMapTemp[i][j] = holeMap[i][j];

	int res = -1;
	while (mK--) {
		holeList.clear();
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				visited[i][j] = false;

		bfs(mRow, mCol, 1);
		bfs(mRow, mCol, -1);

		for (int mID : holesRow[mRow]) 
			if (holeMapTemp[holes[mID].pos.row][holes[mID].pos.col] > 0)
				holeList.push_back(mID);

		for (int mID : holesCol[mCol]) 
			if (holeMapTemp[holes[mID].pos.row][holes[mID].pos.col] > 0)
				holeList.push_back(mID);

		if (holeList.empty())
			break;

		while (!Q.empty()) Q.pop();
		for (int mID : holeList) {
			auto pos = holes[mID].pos;
			int dist = pos.get_dist(mRow, mCol);
			Q.push({ mID, pos.row, pos.col, dist });
		}
		res = Q.top().mID;
		mRow = Q.top().row;
		mCol = Q.top().col;
		holeMapTemp[mRow][mCol] = 0;
	}
	return res;
}
#endif