#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

#define CMD_ADDBOOKINFO 0
#define CMD_ADDBOOKSTOCK 1
#define CMD_SELLBOOKS 2
#define CMD_GETBESTSELLER 3
#define CMD_GETBESTAUTHOR 4
#define CMD_REMOVEBOOKINFO 5

#define BOUND 3
#define MAX_AUTHORS 5

void init(int N, int C);
void addBookInfo(int bID, int cID, int price, int num, int aIDs[]);
void addBookStock(int bID, int cnt);
int sellBooks(int bID, int cnt);
int getBestSeller(int cID, int bIDs[]);
void getBestAuthors(int aIDs[]);
void removeBookInfo(int bID);

static int run()
{
    int N, C, K;
    bool isSuccess = true;

    scanf("%d%d%d", &N, &C, &K);
    init(N, C);
    for (int k = 0; k < K; k++) {
        int cmd = 0;

        if (k == 29) {

            int a = 0;
        }


        scanf("%d", &cmd);
        if (cmd == CMD_ADDBOOKINFO) {
            int bID, cID, price, num;
            int aIDs[MAX_AUTHORS];

            scanf("%d%d%d%d", &bID, &cID, &price, &num);
            for (int i = 0; i < num; i++) {
                scanf("%d", &aIDs[i]);
            }
            addBookInfo(bID, cID, price, num, aIDs);
        }
        else if (cmd == CMD_ADDBOOKSTOCK) {
            int bID, cnt;
            scanf("%d%d", &bID, &cnt);
            addBookStock(bID, cnt);
        }
        else if (cmd == CMD_SELLBOOKS) {
            int bID, cnt, ans;
            scanf("%d%d%d", &bID, &cnt, &ans);
            int ret = sellBooks(bID, cnt);
            if (ret != ans) {
                isSuccess = false;
            }
        }
        else if (cmd == CMD_GETBESTSELLER) {
            int cID, ans, ans_i;
            scanf("%d%d", &cID, &ans);

            int bIDs[BOUND + 5];
            int ret = getBestSeller(cID, bIDs);
            if (ret != ans) {
                isSuccess = false;
            }
            for (int i = 0; i < ans; i++) {
                scanf("%d", &ans_i);
                if (bIDs[i] != ans_i) {
                    isSuccess = false;
                }
            }
        }
        else if (cmd == CMD_GETBESTAUTHOR) {
            int aIDs[BOUND + 5], ans_i;
            getBestAuthors(aIDs);
            for (int i = 0; i < BOUND; i++) {
                scanf("%d", &ans_i);
                if (aIDs[i] != ans_i) {
                    isSuccess = false;
                }
            }
        }
        else if (cmd == CMD_REMOVEBOOKINFO) {
            int bID;
            scanf("%d", &bID);
            removeBookInfo(bID);
        }
    }
    return isSuccess ? 100 : 0;
}

int main()
{
    clock_t start = clock();
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, answer;
    scanf("%d %d", &T, &answer);
    for (int tc = 1; tc <= T; tc++) {
        clock_t tc_start = clock();
        int score = run() ? answer : 0;
        int tc_result = (clock() - tc_start) / (CLOCKS_PER_SEC / 1000);
        printf("#%2d %d (%d ms)\n", tc, score, tc_result);
    }
    int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf(">> Result: %d ms\n", result);
    return 0;
}