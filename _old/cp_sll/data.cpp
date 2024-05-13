#include <cstdio>
#include "data.h"

Data db[] = { { 10, 1 }, { 20, 2 }, { 30, 3 }, { 40, 4 } };
int cnt = 4;

int main()
{
    for (int i = 0; i < cnt; i++)
        printf("%s ", db[i].str().c_str());
    printf("\n");

    for (int i = 0; i < cnt; i++) {
        printf("%s: hash=%d\n", db[i].str().c_str(), std::hash<Data>()(db[i]));
    }

    return 0;
}