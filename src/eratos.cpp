// Sieve of Eratosthenes with prime factorization and divisor enumeration
struct Eratos
{
    Eratos(int table_lim)
        : n(table_lim)
        , e(table_lim, PRIME)
    {
        e[0] = e[1] = 1;
        for (int64_t i = 2; i < n; ++i) {
            if (e[i] == NOT_PRIME)
                continue;
            p.push_back(i);
            for (int64_t j = i * i; j < n; j += i)
                e[j] = NOT_PRIME;
        }
    }

    const int n;
    vector<int> p;  // all primes < n, 0-indexed
    vector<bool> e; // e[i] == PRIME iff i is prime

    // O(1) primality check for x < n
    bool is_prime(int64_t x) { return e[x] == PRIME; }
    bool is_not_prime(int64_t x) { return e[x] == NOT_PRIME; }

    // returns unique prime factors of x (works for x up to n^2)
    vector<int64_t> fact(int64_t x)
    {
        vector<int64_t> res;
        for (int64_t _i = 0, i = p[0]; _i < p.size() && i*i <= x; i = p[++_i]) {
            if (x % i == 0) {
                res.push_back(i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) res.push_back(x);
        return res;
    }

    // returns prime factorization as {prime -> exponent}
    map<int64_t, int> fact_map(int64_t x)
    {
        map<int64_t, int> res;
        for (int64_t _i = 0, i = p[0]; _i < p.size() && i*i <= x; i = p[++_i]) {
            while (x % i == 0) {
                res[i]++;
                x /= i;
            }
        }
        if (x > 1) res[x]++;
        return res;
    }

    // returns all divisors of x (unsorted)
    vector<int64_t> get_divisors(int64_t x)
    {
        int len = 1;
        vector<int64_t> res = {1};

        for (int64_t _i = 0, i = p[0]; _i < p.size() && i*i <= x; i = p[++_i]) {
            if (x % i != 0)
                continue;

            int64_t t = i;
            while (x % i == 0) {
                for (int j = 0; j < len; j++)
                    res.push_back(res[j] * t);
                x /= i;
                t *= i;
            }
            len = res.size();
        }
        if (x > 1) {
            for (int j = 0; j < len; j++)
                res.push_back(res[j] * x);
        }

        return res;
    }

    static constexpr bool PRIME = false;
    static constexpr bool NOT_PRIME = true;

} er(1e7 + 7);

