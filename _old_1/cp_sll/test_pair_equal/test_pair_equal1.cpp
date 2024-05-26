#if 0
#include <cstdio>

template<typename T1, typename T2>
struct Pair {
    T1 key;
    T2 value;
    bool operator==(const Pair& pair) const { return key == pair.key; }
};

struct Data {
    int number, id;
    bool operator==(const Data& data) const { return number == data.number && id == data.id; }
};

Pair<int, int> p1, p2;
Pair<Data, int> d1, d2;

int main()
{
    p1 = { 10, 1 };
    p2 = { 10, 2 };

    d1 = {{10, 1}, {}};
    d2 = {{10, 1}, {}};

    printf("p1 == p2: %d\n", p1 == p2);
    printf("d1 == d2: %d\n", d1 == d2);

    return 0;
}
#endif