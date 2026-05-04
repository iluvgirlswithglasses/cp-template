// Disjoint Set Union with path compression (0-indexed)
struct DSU
{
    vector<int> p;  // parent array

    DSU(int n) : p(n)
    {
        for (int i = 0; i < n; i++)
            p[i] = i;
    }

    // find root of u with path compression, amortized O(α(n))
    int find(int u)
    {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }

    // merge sets containing u and v, returns false if already same set
    bool join(int u, int v)
    {
        int a = find(u), b = find(v);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
};
