// Binary Trie for integers (32-bit), supports insert, remove, k-th largest query
struct Trie {
    struct Node {
        int cnt;           // count of integers ending at this node
        Node* child[2];
        int childcnt[2];   // count of integers in each subtree

        Node() : cnt(0), child{nullptr, nullptr}, childcnt{0, 0} {}
    };

    int n;       // total count of integers in trie
    Node* root;

    Trie() : n(0), root(new Node()) {}

    // insert integer x into trie, O(32)
    void add(int x) {
        n++;
        Node* p = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!p->child[bit])
                p->child[bit] = new Node();
            p->childcnt[bit]++;
            p = p->child[bit];
        }
        p->cnt++;
    }

    // remove one occurrence of integer x from trie, O(32)
    // precondition: x must exist in trie
    void rem(int x) {
        n--;
        Node* p = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            p->childcnt[bit]--;
            p = p->child[bit];
        }
        p->cnt--;
    }

    // returns k-th largest integer (0-indexed), O(32)
    // k=0 returns the largest, k=n-1 returns the smallest
    int kth(int k) {
        int res = 0;
        Node* p = root;
        for (int i = 31; i >= 0; i--) {
            int right_cnt = p->childcnt[1];  // count of larger numbers
            if (right_cnt > k) {
                res |= (1 << i);
                p = p->child[1];
            } else {
                k -= right_cnt;
                p = p->child[0];
            }
        }
        return res;
    }

    int size() const { return n; }
};
