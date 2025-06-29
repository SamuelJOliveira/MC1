#include <iostream>
using namespace std;

    int teto(float n){
        int k = (n >= 0) ? 0 : -1; // n-1 < x <= n

        while (!(k >= n && k-1 < n)){
            k += (n >= 0) ? 1 : -1;
        }    
        
        return k;
    }


    int main() {
        float fn;
        cin >> fn;
        cout << teto(fn) << "\n";
    }