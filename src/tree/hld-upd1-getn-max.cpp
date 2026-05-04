// Heavy-Light Decomposition: point-update + path-max-query (1-indexed)
template <int MAXN>
struct HLD
{
    int n;
    vector<int> adj[MAXN];
    int parent[MAXN], depth[MAXN], subtree[MAXN];
    int chain[MAXN], head[MAXN], pos[MAXN];
    int num_chains, cur_pos;

    int64_t t[MAXN * 2];  // segment tree for point-update + range-max

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // call after adding all edges (init all nodes to -INF)
    void build(int root = 1)
    {
        num_chains = cur_pos = 0;
        fill(head, head + MAXN, 0);
        fill(t, t + MAXN * 2, numeric_limits<int64_t>::min());
        dfs_size(root, 0, -1);
        dfs_hld(root, -1);
    }

    // set value at node u, O(log n)
    void update(int u, int64_t val)
    {
        int p = pos[u] + n;
        t[p] = val;
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = max(t[p<<1], t[p<<1|1]);
    }

    // max value on path u->v, O(log^2 n)
    int64_t path_query(int u, int v)
    {
        int64_t res = numeric_limits<int64_t>::min();
        while (chain[u] != chain[v]) {
            if (depth[head[chain[u]]] < depth[head[chain[v]]]) swap(u, v);
            res = max(res, seg_query(pos[head[chain[u]]], pos[u] + 1));
            u = parent[head[chain[u]]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res = max(res, seg_query(pos[u], pos[v] + 1));
        return res;
    }

    // LCA of u and v, O(log n)
    int lca(int u, int v)
    {
        while (chain[u] != chain[v]) {
            if (depth[head[chain[u]]] < depth[head[chain[v]]]) swap(u, v);
            u = parent[head[chain[u]]];
        }
        return depth[u] < depth[v] ? u : v;
    }

private:
    void dfs_size(int u, int d, int p)
    {
        parent[u] = p;
        depth[u] = d;
        subtree[u] = 1;
        for (int v : adj[u])
            if (v != p) {
                dfs_size(v, d + 1, u);
                subtree[u] += subtree[v];
            }
    }

    void dfs_hld(int u, int p)
    {
        if (head[num_chains] == 0) head[num_chains] = u;
        chain[u] = num_chains;
        pos[u] = cur_pos++;

        int heavy = -1;
        for (int v : adj[u])
            if (v != p && (heavy == -1 || subtree[v] > subtree[heavy]))
                heavy = v;
        if (heavy != -1) dfs_hld(heavy, u);

        for (int v : adj[u])
            if (v != p && v != heavy) {
                num_chains++;
                dfs_hld(v, u);
            }
    }

    int64_t seg_query(int l, int r)
    {
        int64_t res = numeric_limits<int64_t>::min();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};
