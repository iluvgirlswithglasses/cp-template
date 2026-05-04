// Binary exponentiation, O(log b)
int64_t binpow(int64_t a, int64_t b)
{
    int64_t res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// Binary exponentiation with modulo, O(log b)
int64_t binpow(int64_t a, int64_t b, int64_t mod)
{
    int64_t res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
