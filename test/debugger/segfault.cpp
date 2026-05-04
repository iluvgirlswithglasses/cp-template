#include <bits/stdc++.h>
using namespace std;

int main() {
    int* p = nullptr;
    cout << "About to dereference nullptr..." << endl;
    *p = 42;  // segfault here
    return 0;
}
