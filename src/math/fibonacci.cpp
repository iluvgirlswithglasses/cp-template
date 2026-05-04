// Fibonacci using fast doubling, O(log n)
// Returns {F(n), F(n+1)}
pair<int64_t, int64_t> fib(int64_t n)
{
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n >> 1);
    int64_t c = a * (2 * b - a);      // F(2k)
    int64_t d = a * a + b * b;         // F(2k+1)
    if (n & 1) return {d, c + d};
    return {c, d};
}

// Fibonacci with modulo using fast doubling, O(log n)
// Returns {F(n) % mod, F(n+1) % mod}
pair<int64_t, int64_t> fib(int64_t n, int64_t mod)
{
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n >> 1, mod);
    int64_t c = a * ((2 * b - a % mod + mod) % mod) % mod;
    int64_t d = (a * a % mod + b * b % mod) % mod;
    if (n & 1) return {d, (c + d) % mod};
    return {c, d};
}
