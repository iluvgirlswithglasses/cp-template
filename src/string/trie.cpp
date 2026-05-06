// General Trie for strings with configurable alphabet size
// ALPHA_SIZE: number of possible children per node (26 for lowercase, 128 for ASCII)
// BASE: character offset ('a' for lowercase letters, 0 for raw indices)
template<int ALPHA_SIZE = 26, char BASE = 'a'>
struct Trie {
    struct Node {
        int child[ALPHA_SIZE];  // indices into nodes array, -1 if absent
        int cnt;                // count of strings ending here
        int prefix_cnt;         // count of strings passing through this node

        Node() : cnt(0), prefix_cnt(0) {
            fill(child, child + ALPHA_SIZE, -1);
        }
    };

    vector<Node> nodes;

    Trie() { nodes.emplace_back(); }

    // insert string s, O(|s|)
    void insert(const string& s) {
        int p = 0;
        for (char c : s) {
            int idx = c - BASE;
            if (nodes[p].child[idx] == -1) {
                nodes[p].child[idx] = nodes.size();
                nodes.emplace_back();
            }
            p = nodes[p].child[idx];
            nodes[p].prefix_cnt++;
        }
        nodes[p].cnt++;
    }

    // count exact occurrences of string s, O(|s|)
    int count(const string& s) const {
        int p = 0;
        for (char c : s) {
            int idx = c - BASE;
            if (nodes[p].child[idx] == -1) return 0;
            p = nodes[p].child[idx];
        }
        return nodes[p].cnt;
    }

    // count strings with prefix s, O(|s|)
    int count_prefix(const string& s) const {
        int p = 0;
        for (char c : s) {
            int idx = c - BASE;
            if (nodes[p].child[idx] == -1) return 0;
            p = nodes[p].child[idx];
        }
        return nodes[p].prefix_cnt;
    }

    // check if string s exists, O(|s|)
    bool find(const string& s) const { return count(s) > 0; }

    // check if any string starts with prefix s, O(|s|)
    bool starts_with(const string& s) const { return count_prefix(s) > 0; }

    // remove one occurrence of string s, O(|s|)
    // precondition: s must exist in trie
    void erase(const string& s) {
        int p = 0;
        for (char c : s) {
            int idx = c - BASE;
            p = nodes[p].child[idx];
            nodes[p].prefix_cnt--;
        }
        nodes[p].cnt--;
    }
};
