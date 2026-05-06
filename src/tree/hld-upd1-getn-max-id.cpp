// Heavy-Light Decomposition: point-update + path-max-query with node ID (1-indexed)
// Returns both the maximum value and the ID of the node holding that value
template <int MAXN>
struct HLD
{
    struct Node {
        int64_t val;
        int id;
        Node() : val(numeric_limits<int64_t>::min()), id(-1) {}
        Node(int64_t v, int i) : val(v), id(i) {}
    };

    static Node combine(const Node& a, const Node& b) {
        if (a.val > b.val) return a;
        if (b.val > a.val) return b;
        return a.id < b.id ? a : b;  // tie-break by smaller id
    }

    int n;
    vector<int> adj[MAXN];
    int parent[MAXN], depth[MAXN], subtree[MAXN];
    int chain[MAXN], head[MAXN], pos[MAXN];
    int num_chains, cur_pos;

    Node t[MAXN * 2];  // segment tree storing {value, id}

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
        fill(t, t + MAXN * 2, Node());
        dfs_size(root, 0, -1);
        dfs_hld(root, -1);
    }

    // set value and id at node u, O(log n)
    void update(int u, int64_t val, int id)
    {
        int p = pos[u] + n;
        t[p] = Node(val, id);
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = combine(t[p<<1], t[p<<1|1]);
    }

    // max {value, id} on path u->v, O(log^2 n)
    Node path_query(int u, int v)
    {
        Node res;
        while (chain[u] != chain[v]) {
            if (depth[head[chain[u]]] < depth[head[chain[v]]]) swap(u, v);
            res = combine(res, seg_query(pos[head[chain[u]]], pos[u] + 1));
            u = parent[head[chain[u]]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res = combine(res, seg_query(pos[u], pos[v] + 1));
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

    Node seg_query(int l, int r)
    {
        Node res;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = combine(res, t[l++]);
            if (r & 1) res = combine(res, t[--r]);
        }
        return res;
    }
};
