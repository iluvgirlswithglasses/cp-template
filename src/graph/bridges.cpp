// Find bridges in undirected graph (0-indexed)
template <int MAXN>
struct Bridges
{
    int n;
    vector<int> adj[MAXN];
    int tin[MAXN], low[MAXN];
    int timer;
    vector<pair<int, int>> bridges;

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // call after adding all edges, returns list of bridge edges
    vector<pair<int, int>>& build()
    {
        timer = 0;
        fill(tin, tin + n, -1);
        bridges.clear();
        for (int i = 0; i < n; i++)
            if (tin[i] == -1) dfs(i, -1);
        return bridges;
    }

private:
    void dfs(int u, int parent)
    {
        tin[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == parent) continue;
            if (tin[v] != -1) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                    bridges.push_back({u, v});
            }
        }
    }
};
