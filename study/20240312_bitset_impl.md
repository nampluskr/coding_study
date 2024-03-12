### [bitset implementation]

```cpp
#pragma once
#include <cstdio>

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<int len>
struct BitSet {
    char *s, *t;
    int one, zero;

    BitSet() {
        s = new char[len];
        t = new char[len];
        reset();
    }
    ~BitSet() {
        delete[] s;
        delete[] t;
    }

    bool operator[](int idx) const { return s[idx] - '0'; }
    //int test()(int idx) const { return s[idx] - '0'; }
    BitSet& operator|(const BitSet& bit) {
        BitSet res;
        for (int i = 0; i < len; i++)
            if (s[i] | bit.s[i])
                res.s[i] = '1';
        return res;
    }
    //BitSet& operator&(const BitSet& bit) { }
    //BitSet& operator^(const BitSet& bit) { }

    void reset() { 
        one = zero = len;
        for (int i = 0; i < len; i++) { s[i] = '0'; t[i] = '1'; };
    }
    void reset(int idx) { 
        if (s[idx] == '0') { one++; zero--; }
        s[idx] = '0'; t[idx] = '1';
    }
    void set() { 
        one = zero = len;
        for (int i = 0; i < len; i++) { s[i] = '1'; t[i] = '0'; };
    }
    void set(int idx) {
        if (s[idx] == '1') { one--; zero++; }
        s[idx] = '1'; t[idx] = '0';
    }
    void flip() {
        swap(s, t);
        swap(one, zero);
    }
    void flip(int idx) {
        if (s[idx] == '0') { one++; zero--; }
        else { one--; zero++; }
        swap(s[idx], t[idx]);
    }

    int count() { return one; }
    int size() { return len; }

    bool any() { return one != 0; }
    bool none() { return zero == 0; }
    bool all() { return one == len; }

    void show() {
        for (int i = 0; i < len; i++)
            printf("%c", s[i]);
        printf("\n");
    }
};
```

### [main.cpp]

```cpp
#include "bitset.h"
#include <cstdio>

BitSet<10> bitmask, res;

int main()
{
    bitmask.show();
    printf("%d\n", bitmask[0]);
    printf("%d\n", bitmask[1]);

    bitmask.set();
    bitmask.show();
    printf("%d\n", bitmask[0]);
    printf("%d\n", bitmask[1]);

    bitmask.flip();
    bitmask.show();
    printf("%d\n", bitmask[0]);
    printf("%d\n", bitmask[1]);

    res = res | bitmask;
    res.show();

    return 0;
}
```
