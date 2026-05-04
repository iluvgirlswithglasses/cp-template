#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    cout << "Accessing index 100 of size-5 vector..." << endl;
    cout << v[100] << endl;  // OOB access
    return 0;
}
