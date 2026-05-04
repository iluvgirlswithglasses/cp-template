// Combinatorics: nCk (n choose k)

// Basic nCk without modulo, O(k) - use for small values
int64_t comb(int n, int k)
{
    if (k > n || k < 0) return 0;
    if (k > n - k) k = n - k;
    int64_t res = 1;
    for (int i = 0; i < k; i++) {
        res = res * (n - i) / (i + 1);
    }
    return res;
}

// Precomputed factorials for nCk mod p (p must be prime)
template <int MAXN, int64_t MOD>
struct Comb
{
    int64_t fact[MAXN], inv_fact[MAXN];

    Comb() { build(); }

    void build()
    {
        fact[0] = 1;
        for (int i = 1; i < MAXN; i++)
            fact[i] = fact[i-1] * i % MOD;
        inv_fact[MAXN-1] = mod_pow(fact[MAXN-1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; i--)
            inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }

    // nCk mod p, O(1) after precomputation
    int64_t comb(int n, int k)
    {
        if (k > n || k < 0) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
    }

    // nPk (permutations) mod p
    int64_t perm(int n, int k)
    {
        if (k > n || k < 0) return 0;
        return fact[n] * inv_fact[n-k] % MOD;
    }

private:
    int64_t mod_pow(int64_t a, int64_t b)
    {
        int64_t res = 1;
        a %= MOD;
        while (b > 0) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
};
