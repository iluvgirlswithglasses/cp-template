// Manacher's algorithm for finding palindromic substrings in O(n)
struct Manacher
{
    int n;
    vector<int> d_odd;   // d_odd[i] = radius of longest odd palindrome centered at i
    vector<int> d_even;  // d_even[i] = radius of longest even palindrome centered between i and i+1

    // s is 0-indexed
    void build(const string& s)
    {
        n = s.size();
        d_odd.assign(n, 0);
        d_even.assign(n, 0);
        calc_odd(s);
        calc_even(s);
    }

    // length of longest odd palindrome centered at i: 2*d_odd[i] + 1
    // length of longest even palindrome centered between i and i+1: 2*d_even[i]

    // check if s[l..r] is a palindrome in O(1)
    bool is_palindrome(int l, int r)
    {
        int len = r - l + 1;
        int mid = (l + r) / 2;
        if (len & 1)
            return d_odd[mid] >= len / 2;
        else
            return d_even[mid] >= len / 2;
    }

private:
    void calc_odd(const string& s)
    {
        int l = 0, r = -1;
        for (int i = 0; i < n; i++) {
            int k = (i > r) ? 0 : min(r - i, d_odd[l + r - i]);
            while (i - k - 1 >= 0 && i + k + 1 < n && s[i - k - 1] == s[i + k + 1])
                k++;
            d_odd[i] = k;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
    }

    void calc_even(const string& s)
    {
        int l = 0, r = -1;
        for (int i = 0; i < n - 1; i++) {
            int j = i + 1;
            int k = (j > r) ? 0 : min(r - j + 1, d_even[l + r - j]);
            while (i - k >= 0 && j + k < n && s[i - k] == s[j + k])
                k++;
            d_even[i] = k;
            if (j + k - 1 > r) {
                l = i - k + 1;
                r = j + k - 1;
            }
        }
    }
};
