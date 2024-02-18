#if 0
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

#define MAX_N		(3000 + 1)
#define MAX_HOLES	(30000 + 1)

struct Position {
	int row, col;
	bool operator<(const Position& pos) const {
		return (row > pos.row) || (row == pos.row && col > pos.col);
	}
};

unordered_map<int, Position> holes;
int holeID[MAX_N][MAX_N];
set<int> holesRow[MAX_N];
set<int> holesCol[MAX_N];
set<Position> holesDiag[MAX_N][MAX_N][2];

/////////////////////////////////////////////////////////////////////
void init(int N)
{
	holes.clear();
	for (int i = 1; i <= N; i++) {
		holesRow[i].clear();
		holesCol[i].clear();
		for (int j = 1; j <= N; j++) {
			holesDiag[i][j][0].clear();
			holesDiag[i][j][1].clear();
			holeID[i][j] = 0;
		}
	}

}

void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)
{
	if (mBCol < mACol) { swap(mACol, mBCol); swap(mARow, mBRow); }

	int slope = (mARow < mBRow) ? 1 : -1;
	Position cur = { mARow, mACol };

	for (int col = mACol + 1; col <= mBCol; col++) {
		Position next = { slope * (col - cur.col) + cur.row, col };
		if (slope == 1) {
			holesDiag[cur.row][cur.col][0].insert(next);
			holesDiag[next.row][next.col][0].insert(cur);
		}
		else {
			holesDiag[cur.row][cur.col][1].insert(next);
			holesDiag[next.row][next.col][1].insert(cur);
		}
		cur = next;
	}
}

void addHole(int mRow, int mCol, int mID)
{
	holesRow[mRow].insert(mID);
	holesCol[mCol].insert(mID);

	holes.insert({ mID, { mRow, mCol } });
	holeID[mRow][mCol] = mID;
}

void eraseHole(int mRow, int mCol)
{
	holesRow[mRow].erase(mCol);
	holesCol[mCol].erase(mRow);

	int mID = holeID[mRow][mCol];
	holes.erase(mID);
	holeID[mRow][mCol] = 0;
}

int hitMarble(int mRow, int mCol, int mK)
{

	return 0;
}
#endif