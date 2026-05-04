// Point-update, range-max segment tree (iterative, 0-indexed, half-open intervals)
template <typename T>
struct MaxSegtree
{
    vector<T> t;
    const int n;

    MaxSegtree(int size): n(size), t(n << 1) {}

    // set leaf value before build (pos in [0, n))
    void init_set(int pos, T v) { t[pos + n] = v; }

    void init_set(T* begin, T* end)
    {
        int i = n;
        while (begin < end) {
            t[i++] = *begin;
            ++begin;
        }
    }

    // call after all init_set calls to build internal nodes
    void init_build()
    {
        for (int i = n - 1; i > 0; --i)
            t[i] = max(t[i<<1], t[i<<1|1]);
    }

    // set a[p] = v and update tree, O(log n)
    void upd(int p, T v)
    {
        t[p += n] = v;
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = max(t[p<<1], t[p<<1|1]);
    }

    // max over [l, r), O(log n)
    T query(int l, int r)
    {
        T ans = numeric_limits<T>::min();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans = max(ans, t[l++]);
            if (r&1) ans = max(ans, t[--r]);
        }
        return ans;
    }

};

