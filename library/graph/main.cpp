extern void test_dfs(int option);
extern void test_bfs(int option);
extern void test_dfs_findAPath(int option);
extern void test_bfs_findAPath(int option);
extern void test_findAllPaths(int option);
extern void test_maxCostPath(int option);

int main()
{
    test_dfs(1);
    test_bfs(1);

    test_dfs_findAPath(0);
    test_bfs_findAPath(0);

    test_findAllPaths(0);

    test_maxCostPath(0);

    return 0;
}