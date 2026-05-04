// Range-add-update, point-query segment tree (iterative, 0-indexed, half-open intervals)
template <typename T>
struct AddSegtree
{
    const int n;
    vector<T> t;

    AddSegtree(int size): n(size), t(n << 1) {}

    // set initial value at pos before build (pos in [0, n))
    void init_set(int pos, T v) { t[pos + n] = v; }

    void init_set(T* begin, T* end)
    {
        int i = n;
        while (begin < end) {
            t[i++] = *begin;
            ++begin;
        }
    }

    // call after all init_set calls (pushes leaf values to internal nodes)
    void init_build()
    {
        for (int i = n - 1; i > 0; --i) {
            t[i<<1] += t[i];
            t[i<<1|1] += t[i];
            t[i] = 0;
        }
    }

    // add v to all elements in [l, r), O(log n)
    void add(int l, int r, T v)
    {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) t[l++] += v;
            if (r&1) t[--r] += v;
        }
    }

    // get value at position p, O(log n)
    T query(int p)
    {
        T ans = 0;
        for (p += n; p > 0; p >>= 1)
            ans += t[p];
        return ans;
    }
};
