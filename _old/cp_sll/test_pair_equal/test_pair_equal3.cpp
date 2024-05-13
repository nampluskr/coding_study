#if 1
#include <cstdio>
#include "linked_list.h"
#include "hash_map.h"

struct Data {
    int number, id;
    bool operator==(const Data& data) const { return number == data.number && id == data.id; }
    int hash(int max_table) const { return (number * 1000 + id) % max_table; }
};

HashMap<Data, int> map;

int main()
{
    Data d1{10, 1}, d2{20, 2}, d3{30, 3}, d4{40, 4};
    
    printf("\n*** Insert\n");
    // map.insert(d1, 1111);
    // map.insert(d2, 2222);
    // map.insert(d3, 3333);

    map[d1] = 1111;
    map[d2] = 2222;
    map[d3] = 3333;

    printf("map[d1] = %d\n", map.find(d1));
    printf("map[d2] = %d\n", map.find(d2));
    printf("map[d3] = %d\n", map.find(d3));
    printf("map[d4] = %d\n", map.find(d4));

    printf("\n*** Erase\n");
    map.erase(d1);
    map.erase(d2);
    map.erase(d3);
    map.insert(d4, 4444);

    printf("map[d1] = %d\n", map.find(d1));
    printf("map[d2] = %d\n", map.find(d2));
    printf("map[d3] = %d\n", map.find(d3));
    printf("map[d4] = %d\n", map.find(d4));

    return 0;
}
#endif