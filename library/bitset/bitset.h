#pragma once

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<int len>
struct BitSet {
    bool* bits, * flipped;
    int ones, zeros;

    BitSet() {
        bits = new bool[len];
        flipped = new bool[len];
        reset();
    }
    //~BitSet() {
    //    delete[] bits;
    //    delete[] flipped;
    //}

    void reset(int idx) {
        if (bits[idx] == 1) { ones--; zeros++; }
        bits[idx] = 0; flipped[idx] = 1;
    }
    void reset() {
        ones = zeros = len;
        for (int i = 0; i < len; i++) { bits[i] = 0; flipped[i] = 1; }
    }
    void set(int idx) {
        if (bits[idx] == 0) { ones++; zeros--; }
        bits[idx] = 1; flipped[idx] = 0;
    }
    void set() {
        ones = zeros = len;
        for (int i = 0; i < len; i++) { bits[i] = 1; flipped[i] = 0; }
    }
    void flip() {
        swap(bits, flipped);
        swap(ones, zeros);
    }
    int count() { return ones; }
    int size() { return len; }

    bool operator[](int idx) const { return bits[idx]; }

    BitSet& operator|(const BitSet& b) {
        BitSet res;
        res.ones = res.zeros = 0;
        for (int i = 0; i < len; i++) {
            res.bits[i] = bits[i] || b.bits[i];
            res.flipped[i] = !res.bits[i];
            if (res.bits[i]) res.ones++;
            else res.zeros++;
        }
        return res;
    }
    //BitSet& operator&(BitSet& b) {
    //    BitSet res;
    //    res.ones = res.zeros = 0;
    //    for (int i = 0; i < len; i++) {
    //        res.bits[i] = bits[i] & b.bits;
    //        res.flipped[i] = !res.bits[i];
    //        if (res.bits[i]) res.ones++;
    //        else res.zeros++;
    //    }
    //    return res;
    //}
};