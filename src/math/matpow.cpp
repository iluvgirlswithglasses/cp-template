// Matrix exponentiation for linear recurrences, O(K^3 log n)
// K = matrix dimension, n = exponent
// Use case: compute n-th term of linear recurrence in O(log n)

template <int K, int64_t MOD = 0>
struct Matrix {
    int64_t a[K][K];

    Matrix() { memset(a, 0, sizeof(a)); }

    // identity matrix
    static Matrix I() {
        Matrix m;
        for (int i = 0; i < K; i++) m.a[i][i] = 1;
        return m;
    }

    Matrix operator*(const Matrix& o) const {
        Matrix res;
        for (int i = 0; i < K; i++)
            for (int j = 0; j < K; j++)
                for (int k = 0; k < K; k++) {
                    res.a[i][j] += a[i][k] * o.a[k][j];
                    if constexpr (MOD > 0) res.a[i][j] %= MOD;
                }
        return res;
    }

    // matrix exponentiation, O(K^3 log n)
    Matrix pow(int64_t n) const {
        Matrix res = I(), base = *this;
        while (n > 0) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
};

// Example: Fibonacci using matrix exponentiation
// F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
// [F(n+1)]   [1 1]^n   [1]
// [F(n)  ] = [1 0]   * [0]
template <int64_t MOD = 0>
int64_t fib_matrix(int64_t n) {
    if (n == 0) return 0;
    Matrix<2, MOD> m;
    m.a[0][0] = m.a[0][1] = m.a[1][0] = 1;
    m.a[1][1] = 0;
    auto res = m.pow(n - 1);
    return res.a[0][0];  // F(n)
}

// Example: General k-th order linear recurrence
// a_n = c[0]*a_{n-1} + c[1]*a_{n-2} + ... + c[k-1]*a_{n-k}
// Transition matrix (k x k):
// [c[0] c[1] c[2] ... c[k-1]]
// [1    0    0    ... 0     ]
// [0    1    0    ... 0     ]
// [...  ...  ...  ... ...   ]
// [0    0    ...  1   0     ]
