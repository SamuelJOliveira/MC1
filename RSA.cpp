

        
#include <iostream>
#include <string>
using namespace std;

// 1) Teste de primalidade: trial division contando divisores
bool ehPrime(long long n) {
    if (n < 2) return false;
    int count = 0;
    for (long long i = 1; i <= n; ++i) {
        if (n % i == 0) ++count;
    }
    return count == 2;  // só 1 e n dividem
}

// 2) Algoritmo de Euclides para gcd(a,b)
long long mdc(long long a, long long b) {
    return b == 0 ? a : mdc(b, a % b);
}

// 3) Euclides estendido: encontra x,y tais que a*x + b*y = gcd(a,b)
long long bezout(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long g = bezout(b, a % b, x1, y1);
    long long q = a / b;
    x = y1;
    y = x1 - q * y1;
    return g;
}

// 4) Expoção modular ingênua: calcula (base^exp) mod mod
long long modexp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    for (long long i = 0; i < exp; ++i) {
        res = (res * base) % mod;
    }
    return res;
}

int main() {
    long long p, q, e;
    string texto;

    // Leitura de p e q: devem ser primos e distintos
    do {
        cout << "Digite dois primos distintos p e q: ";
        cin >> p >> q;
        if (!ehPrime(p) || !ehPrime(q))
            cout << "Erro: p e q devem ser primos.\n";
        else if (p == q)
            cout << "Erro: p e q devem ser diferentes.\n";
    } while (!ehPrime(p) || !ehPrime(q) || p == q);

    // Cálculo de phi = (p-1)*(q-1) e leitura de e válido
    long long phi = (p - 1) * (q - 1);
    do {
        cout << "Digite o expoente publico e (1 < e < " << phi
             << " e gcd(e,phi)=1): ";
        cin >> e;
    } while (e <= 1 || e >= phi || mdc(e, phi) != 1);

    // Limpa buffer e lê texto puro (apenas A–Z)
    cin.ignore();
    cout << "Digite texto puro (A–Z): ";
    getline(cin, texto);

    // Geração de n e da chave privada d
    long long n = p * q;
    long long x, y;
    bezout(e, phi, x, y);
    long long d = x % phi;
    if (d < 0) d += phi;  // garante 0 ≤ d < phi

    // --- Encriptação letra por letra ---
    cout << "\nTexto cifrado:\n";
    for (int i = 0; i < (int)texto.size(); ++i) {
        char ch = texto[i];
        // mapeia 'A'→10, 'B'→11, …, 'Z'→35
        long long m = (ch - 'A') + 10;
        long long c = modexp(m, e, n);
        cout << c << ' ';
    }
    cout << "\n";

    // --- Decriptação dos mesmos valores ---
    cout << "\nTexto decifrado:\n";
    for (int i = 0; i < (int)texto.size(); ++i) {
        char ch = texto[i];
        long long m = (ch - 'A') + 10;
        long long c = modexp(m, e, n);
        long long m2 = modexp(c, d, n);
        // reconverte 10→'A', …, 35→'Z'
        char out = char((m2 - 10) + 'A');
        cout << out;
    }
    cout << "\n";

    return 0;
}

