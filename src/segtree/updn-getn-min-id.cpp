// Range-increment, range-min segment tree with ID tracking and lazy propagation (0-indexed, half-open)
// Returns both the minimum value and the ID of the element holding that value
template <typename T>
struct MinSegtree
{
    struct Node {
        T val;
        int id;
        Node() : val(numeric_limits<T>::max()), id(-1) {}
        Node(T v, int i) : val(v), id(i) {}
    };

    static Node combine(const Node& a, const Node& b) {
        if (a.val < b.val) return a;
        if (b.val < a.val) return b;
        return a.id < b.id ? a : b;  // tie-break by smaller id
    }

    const int n, h;
    vector<Node> t;  // tree nodes
    vector<T> d;     // lazy deltas for internal nodes

    MinSegtree(int size)
        : n(size)
        , h(32 - __builtin_clz(n))
    {
        t.resize(n << 1);
        d.resize(n);
    }

    // set leaf value and id before build (pos in [0, n))
    void init_set(int pos, T v, int id) { t[pos + n] = Node(v, id); }

    // call after all init_set calls to build internal nodes
    void init_build()
    {
        for (int i = n - 1; i >= 1; --i)
            t[i] = combine(t[i<<1], t[i<<1|1]);
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

    // min {value, id} over [l, r), O(log n)
    Node query(int l, int r) {
        l += n, r += n;
        push(l);
        push(r - 1);
        Node res;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = combine(res, t[l++]);
            if (r&1) res = combine(t[--r], res);
        }
        return res;
    }

private:
    void apply(int p, T value)
    {
        t[p].val += value;
        if (p < n) d[p] += value;
    }

    void build(int p)
    {
        while (p > 1) {
            p >>= 1;
            t[p] = combine(t[p<<1], t[p<<1|1]);
            t[p].val += d[p];
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
