#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// 1) Teste de primalidade
bool ehPrimo(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

// 2) GCD recursivo
long long mdc(long long a, long long b) {
    return b == 0 ? a : mdc(b, a % b);
}

// 3) Euclides estendido
long long bezout(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long g = bezout(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// 4) Inverso modular (garante 0 ≤ inv < m)
long long inversoModular(long long a, long long m) {
    long long x, y;
    long long g = bezout(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// 5) Exponenciação modular rápida
long long exponenciacaoModular(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// 6) RSA (cifra e decifra)
string rsa(const string &texto, bool cifrar, long long p, long long q) {
    if (!ehPrimo(p) || !ehPrimo(q) || p == q)
        return "ERRO";

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    // escolhe e
    long long e = 3;
    while (e < phi && mdc(e, phi) != 1) e += 2;

    long long d = inversoModular(e, phi);
    if (d < 0)
        return "ERRO";

    // DEBUG: mostre esses valores para conferir
    cout << "[DEBUG] n="<<n<<" φ(n)="<<phi<<" e="<<e<<" d="<<d<<"\n";

    if (cifrar) {
        string codificado;
        for (unsigned char ch : texto) {
            long long m = ch;
            long long c = exponenciacaoModular(m, e, n);
            codificado += to_string(c) + ' ';
        }
        return codificado;
    }
    else {
        string decodificado = "";
        string bloco;
        size_t i = 0;

        // percorre toda a string “texto” contendo os números cifrados
        while (i < texto.length()) {
            // pula quaisquer espaços
            if (texto[i] == ' ') {
                ++i;
                continue;
            }

            // monta o próximo bloco numérico até encontrar espaço
            bloco.clear();
            while (i < texto.length() && texto[i] != ' ') {
                bloco += texto[i++];
            }

            // converte string → inteiro c
            long long c = stoll(bloco);

            // aplica c^d mod n, obtendo o valor ASCII original
            long long m = exponenciacaoModular(c, d, n);

            // anexa o caractere correspondente ao código m (0–255)
            decodificado += static_cast<char>(m);
        }

        return decodificado;
    }
}

int main() {
    long long p, q;
    cout << "Digite dois numeros primos p e q: ";
    if (!(cin >> p >> q)) return 0;
    cin.ignore();  // descarta '\n'

    string mensagem;
    cout << "Mensagem para cifrar: ";
    getline(cin, mensagem);

    string cifrado = rsa(mensagem, true, p, q);
    cout << "Texto cifrado: " << cifrado << "\n";

    string decifrado = rsa(cifrado, false, p, q);
    cout << "Texto decifrado: " << decifrado << "\n";

    return 0;
}
