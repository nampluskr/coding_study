int sqrt(int n) {
    double x1 = n, x2 = (x1 + n / x1) / 2;
    while (x1 - x2 > 0.1) { x1 = x2; x2 = (x1 + n / x1) / 2; }
    return x2;
}

int ceil(int a, int b) { return (a + b - 1) / b; }
int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a < b) ? b : a; }