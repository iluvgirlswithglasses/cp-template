#include <bits/stdc++.h>
using namespace std;

int fib(int n) {
    if (n < 0) return fib(n - 1) + fib(n - 2);  // bug: should be n <= 1
    return fib(n - 1) + fib(n - 2);  // infinite recursion
}

int main() {
    cerr << "Calling buggy fib(10)..." << endl;
    cout << fib(10) << endl;
    return 0;
}
