// Fast doubling template for divide-and-conquer recurrences, O(log n)
// Use case: compute a(n) when a(2k) and a(2k+1) can be expressed in terms of a(k) and a(k+1)
//
// Pattern: given state [a(k), a(k+1)], derive [a(2k), a(2k+1), a(2k+2)]
// Then return appropriate pair based on n's parity
//
// Examples:
// - Fibonacci: F(2k) = F(k)*(2*F(k+1) - F(k)), F(2k+1) = F(k)^2 + F(k+1)^2
// - Custom: a(2k) = 2*a(k), a(2k+1) = a(k) - 3*a(k+1)

template <int64_t MOD = 0>
struct FastDoubling {
    // Override these for your specific recurrence
    // Returns {a(2k), a(2k+1), a(2k+2)} given {a(k), a(k+1)}
    static tuple<int64_t, int64_t, int64_t> double_step(int64_t ak, int64_t ak1) {
        // Example: a(2k) = 2*a(k), a(2k+1) = a(k) - 3*a(k+1)
        int64_t a2k = 2 * ak;
        int64_t a2k1 = ak - 3 * ak1;
        int64_t a2k2 = 2 * ak1;
        if constexpr (MOD > 0) {
            a2k %= MOD;
            a2k1 = ((a2k1 % MOD) + MOD) % MOD;
            a2k2 %= MOD;
        }
        return {a2k, a2k1, a2k2};
    }

    // Returns {a(n), a(n+1)}
    // Base cases: a(0), a(1), a(2) must be known
    static pair<int64_t, int64_t> compute(int64_t n, int64_t a0, int64_t a1, int64_t a2) {
        if (n == 0) return {a0, a1};
        if (n == 1) return {a1, a2};

        auto [ak, ak1] = compute(n >> 1, a0, a1, a2);
        auto [a2k, a2k1, a2k2] = double_step(ak, ak1);

        if (n % 2 == 0) return {a2k, a2k1};
        return {a2k1, a2k2};
    }

    // Convenience: returns just a(n)
    static int64_t get(int64_t n, int64_t a0, int64_t a1, int64_t a2) {
        return compute(n, a0, a1, a2).first;
    }
};

// Fibonacci specialization: F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
template <int64_t MOD = 0>
struct FibDoubling {
    static pair<int64_t, int64_t> compute(int64_t n) {
        if (n == 0) return {0, 1};
        auto [fk, fk1] = compute(n >> 1);

        // F(2k) = F(k) * (2*F(k+1) - F(k))
        // F(2k+1) = F(k)^2 + F(k+1)^2
        int64_t f2k, f2k1;
        if constexpr (MOD > 0) {
            f2k = fk * ((2 * fk1 - fk % MOD + MOD) % MOD) % MOD;
            f2k1 = (fk * fk % MOD + fk1 * fk1 % MOD) % MOD;
        } else {
            f2k = fk * (2 * fk1 - fk);
            f2k1 = fk * fk + fk1 * fk1;
        }

        if (n % 2 == 0) return {f2k, f2k1};
        int64_t f2k2 = (MOD > 0) ? (f2k + f2k1) % MOD : f2k + f2k1;
        return {f2k1, f2k2};
    }

    static int64_t get(int64_t n) { return compute(n).first; }
};
