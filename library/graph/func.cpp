#include <vector>
#include <cstdio>

void print_list(const std::vector<int> list) {
    if (!list.empty()) {
        printf(">> ");
        for (int i = 0; i < list.size() - 1; i++)
            printf("[%d]->", list[i]);
        printf("[%d]\n", list.back());
    }
    else {
        printf(">> Empty!\n");
    }
}