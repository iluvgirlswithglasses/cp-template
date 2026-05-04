// Tarjan's algorithm for Strongly Connected Components (0-indexed)
template <int MAXN>
struct TarjanSCC
{
    int n;
    vector<int> adj[MAXN];
    int tin[MAXN], low[MAXN], comp[MAXN];  // discovery time, low-link, component id
    int timer, num_scc;
    vector<int> st;
    bool on_stack[MAXN];

    void add_edge(int u, int v) { adj[u].push_back(v); }

    // call after adding all edges, returns number of SCCs
    int build()
    {
        timer = num_scc = 0;
        fill(tin, tin + n, -1);
        fill(on_stack, on_stack + n, false);
        st.clear();
        for (int i = 0; i < n; i++)
            if (tin[i] == -1) dfs(i);
        return num_scc;
    }

    // check if u and v are in the same SCC
    bool same(int u, int v) { return comp[u] == comp[v]; }

private:
    void dfs(int u)
    {
        tin[u] = low[u] = timer++;
        st.push_back(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (tin[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            while (true) {
                int v = st.back();
                st.pop_back();
                on_stack[v] = false;
                comp[v] = num_scc;
                if (v == u) break;
            }
            num_scc++;
        }
    }
};
