// Find articulation points (cut vertices) in undirected graph (0-indexed)
template <int MAXN>
struct ArticulationPoints
{
    int n;
    vector<int> adj[MAXN];
    int tin[MAXN], low[MAXN];
    int timer;
    bool is_cut[MAXN];  // is_cut[u] = true if u is articulation point
    vector<int> cuts;

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // call after adding all edges, returns list of articulation points
    vector<int>& build()
    {
        timer = 0;
        fill(tin, tin + n, -1);
        fill(is_cut, is_cut + n, false);
        cuts.clear();
        for (int i = 0; i < n; i++)
            if (tin[i] == -1) dfs(i, -1);
        return cuts;
    }

private:
    void dfs(int u, int parent)
    {
        tin[u] = low[u] = timer++;
        int children = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            if (tin[v] != -1) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= tin[u] && parent != -1 && !is_cut[u]) {
                    is_cut[u] = true;
                    cuts.push_back(u);
                }
                children++;
            }
        }
        if (parent == -1 && children > 1 && !is_cut[u]) {
            is_cut[u] = true;
            cuts.push_back(u);
        }
    }
};
