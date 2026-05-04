// LCA using Euler tour + sparse table (0 or 1-indexed, configure ROOT)
template <int MAXN>
struct LCA
{
    static constexpr int LOG = 32 - __builtin_clz(MAXN);

    int n;
    vector<int> adj[MAXN];
    int depth[MAXN], first[MAXN], parent[MAXN];
    vector<int> euler;
    int sparse[LOG][MAXN * 2];  // sparse[k][i] = argmin depth in euler[i..i+2^k)

    // call after adding all edges
    void build(int root = 1)
    {
        euler.clear();
        euler.reserve(n * 2);
        dfs(root, 0, -1);
        build_sparse();
    }

    // add undirected edge (call before build)
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // LCA query, O(1)
    int query(int u, int v)
    {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        return rmq(l, r + 1);
    }

    // distance between u and v
    int dist(int u, int v)
    {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }

private:
    void dfs(int u, int d, int p)
    {
        parent[u] = p;
        depth[u] = d;
        first[u] = euler.size();
        euler.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, d + 1, u);
                euler.push_back(u);
            }
        }
    }

    void build_sparse()
    {
        int m = euler.size();
        for (int i = 0; i < m; i++)
            sparse[0][i] = euler[i];
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i + (1 << k) <= m; i++) {
                int a = sparse[k-1][i];
                int b = sparse[k-1][i + (1 << (k-1))];
                sparse[k][i] = (depth[a] < depth[b]) ? a : b;
            }
        }
    }

    int rmq(int l, int r)
    {
        int k = 31 - __builtin_clz(r - l);
        int a = sparse[k][l];
        int b = sparse[k][r - (1 << k)];
        return (depth[a] < depth[b]) ? a : b;
    }
};
