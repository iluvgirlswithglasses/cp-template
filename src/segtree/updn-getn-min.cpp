// Range-increment, range-min segment tree with lazy propagation (0-indexed, half-open)
template <typename T>
struct MinSegtree
{
    const int n, h;
    vector<T> t;  // tree nodes
    vector<T> d;  // lazy deltas for internal nodes

    MinSegtree(int size)
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
            t[i] = min(t[i<<1], t[i<<1|1]);
    }

    // add value to all elements in [l, r), O(log n)
    void inc(int l, int r, T value)
    {
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, value);
            if (r&1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }

    // min over [l, r), O(log n)
    T query(int l, int r) {
        l += n, r += n;
        push(l);
        push(r - 1);
        T res = numeric_limits<T>::max();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(t[--r], res);
        }
        return res;
    }

private:
    void apply(int p, T value)
    {
        t[p] += value;
        if (p < n) d[p] += value;
    }

    void build(int p)
    {
        while (p > 1) {
            p >>= 1;
            t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
        }
    }

    void push(int p)
    {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
        }
    }
};
