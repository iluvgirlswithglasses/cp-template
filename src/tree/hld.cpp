// Heavy-Light Decomposition for path updates/queries (1-indexed)
// Supports: path increment + point query (modify segtree for other operations)
template <int MAXN>
struct HLD
{
    int n;
    vector<int> adj[MAXN];
    int parent[MAXN], depth[MAXN], subtree[MAXN];
    int chain[MAXN], head[MAXN], pos[MAXN];  // chain id, chain head, position in flat array
    int num_chains, cur_pos;

    // segment tree for range-add + point-query on flattened tree
    int64_t t[MAXN * 2];

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // call after adding all edges
    void build(int root = 1)
    {
        num_chains = cur_pos = 0;
        fill(head, head + MAXN, 0);
        fill(t, t + MAXN * 2, 0);
        dfs_size(root, 0, -1);
        dfs_hld(root, -1);
    }

    // add val to all nodes on path u->v, O(log^2 n)
    void path_add(int u, int v, int64_t val)
    {
        while (chain[u] != chain[v]) {
            if (depth[head[chain[u]]] < depth[head[chain[v]]]) swap(u, v);
            seg_add(pos[head[chain[u]]], pos[u] + 1, val);
            u = parent[head[chain[u]]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        seg_add(pos[u], pos[v] + 1, val);
    }

    // get value at node u, O(log n)
    int64_t point_query(int u)
    {
        int64_t res = 0;
        for (int i = pos[u] + n; i > 0; i >>= 1)
            res += t[i];
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
        for (int v : adj[u]) {
            if (v != p) {
                dfs_size(v, d + 1, u);
                subtree[u] += subtree[v];
            }
        }
    }

    void dfs_hld(int u, int p)
    {
        if (head[num_chains] == 0) head[num_chains] = u;
        chain[u] = num_chains;
        pos[u] = cur_pos++;

        // find heavy child (largest subtree)
        int heavy = -1;
        for (int v : adj[u]) {
            if (v != p && (heavy == -1 || subtree[v] > subtree[heavy]))
                heavy = v;
        }
        if (heavy != -1) dfs_hld(heavy, u);

        // light children start new chains
        for (int v : adj[u]) {
            if (v != p && v != heavy) {
                num_chains++;
                dfs_hld(v, u);
            }
        }
    }

    void seg_add(int l, int r, int64_t val)
    {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += val;
            if (r & 1) t[--r] += val;
        }
    }
};
