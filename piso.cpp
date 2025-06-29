#include <iostream>
using namespace std;


 int piso(float n) {  // n <= x < n+1
    int k = (n >= 0) ? 0 : -1;
    // Se n é positivo, começa em 0; se negativo, começa em -1.
    while (!(k <= n && k + 1 > n)) {
        k += (n >= 0) ? 1 : -1;
    }

    return k;
    }

    // main piso
    int main() {
        float fn;
        cin >> fn;
        cout << piso(fn) << "\n";
    } 