// Find gcd(a, b), O(log n)
int64_t gcd(int64_t a, int64_t b) {
    int64_t r;
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Find lcm(a, b) using gcd(a, b)
int64_t lcm(int64_t a, int64_t b) {
	int64_t c = gcd(a, b);
	return c * (a/c) * (b/c);
}
