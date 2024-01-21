int rand(int seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

int ceil(int a, int b) {
    return (a + b - 1) / b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a < b) ? b : a;
}

int sqrt(int n) {
    double x1 = n, x2 = (x1 + n / x1) / 2;
    while (x1 - x2 > 0.01) { x1 = x2, x2 = (x1 + n / x1) / 2; }
    return (int)x2;
}