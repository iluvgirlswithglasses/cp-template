// Point-update, range-max segment tree with ID tracking (iterative, 0-indexed, half-open)
// Returns both the maximum value and the ID of the element holding that value
template <typename T>
struct MaxSegtree
{
    struct Node {
        T val;
        int id;
        Node() : val(numeric_limits<T>::min()), id(-1) {}
        Node(T v, int i) : val(v), id(i) {}
    };

    static Node combine(const Node& a, const Node& b) {
        if (a.val > b.val) return a;
        if (b.val > a.val) return b;
        return a.id < b.id ? a : b;  // tie-break by smaller id
    }

    const int n;
    vector<Node> t;

    MaxSegtree(int size): n(size), t(n << 1) {}

    // set leaf value and id before build (pos in [0, n))
    void init_set(int pos, T v, int id) { t[pos + n] = Node(v, id); }

    // call after all init_set calls to build internal nodes
    void init_build()
    {
        for (int i = n - 1; i > 0; --i)
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    // set a[p] = {v, id} and update tree, O(log n)
    void upd(int p, T v, int id)
    {
        t[p += n] = Node(v, id);
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = combine(t[p<<1], t[p<<1|1]);
    }

    // max {value, id} over [l, r), O(log n)
    Node query(int l, int r)
    {
        Node ans;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans = combine(ans, t[l++]);
            if (r&1) ans = combine(ans, t[--r]);
        }
        return ans;
    }
};
