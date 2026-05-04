// Range-increment, range-sum segment tree with lazy propagation (0-indexed, half-open)
template <typename T>
struct SumSegtree
{
    const int n, h;
    vector<T> t;  // tree nodes (sums)
    vector<T> d;  // lazy deltas for internal nodes

    SumSegtree(int size)
        : n(size)
        , h(32 - __builtin_clz(n))
    {
        t.resize(n << 1);
        d.resize(n);
    }

    // set leaf value before build (pos in [0, n))
    void init_set(int pos, T v) { t[pos + n] = v; }

    // call after all init_set calls to build internal nodes
    void init_build()
    {
        for (int i = n - 1; i >= 1; --i)
            t[i] = t[i<<1] + t[i<<1|1];
    }

    // add value to all elements in [l, r), O(log n)
    void inc(int l, int r, T value)
    {
        l += n, r += n;
        int l0 = l, r0 = r, len = 1;
        for (; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (l&1) apply(l++, value, len);
            if (r&1) apply(--r, value, len);
        }
        build(l0);
        build(r0 - 1);
    }

    // sum over [l, r), O(log n)
    T query(int l, int r)
    {
        l += n, r += n;
        push(l);
        push(r - 1);
        T res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }

private:
    void apply(int p, T value, int len)
    {
        t[p] += value * len;
        if (p < n) d[p] += value;
    }

    void build(int p)
    {
        int len = 1;
        while (p > 1) {
            p >>= 1;
            len <<= 1;
            t[p] = t[p<<1] + t[p<<1|1] + d[p] * len;
        }
    }

    void push(int p)
    {
        for (int s = h, len = 1 << (h - 1); s > 0; --s, len >>= 1) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i], len);
                apply(i<<1|1, d[i], len);
                d[i] = 0;
            }
        }
    }
};
