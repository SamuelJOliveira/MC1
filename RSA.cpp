#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// 1) Teste de primalidade: trial division contando divisores
bool ehPrimo(long long n) {
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

// 4) Inverso modular: retorna x tal que (a * x) % m == 1, ou -1 se não existir
long long inversoModular(long long a, long long m) {
    long long x, y;
    long long g = bezout(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// 5) Expoção modular ingênua: calcula (base^exp) mod mod
long long exponenciacaoModular(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    for (long long i = 0; i < exp; ++i) {
        res = (res * base) % mod;
    }
    return res;
}

// 6) RSA: cifrar=true para encriptar, false para decriptar
string rsa(const string &texto, bool cifrar, long long p, long long q) {
    if (!ehPrimo(p) || !ehPrimo(q) || p == q) {
        return "ERRO";
    }

    long long n = p * q;
    long long totiente = (p - 1) * (q - 1);

    // escolhe e padrão se coprimo, senão busca próximo ímpar
    long long e = 0;
    if (65537 < totiente && mdc(65537, totiente) == 1) {
        e = 65537;
    }
    else if (17 < totiente && mdc(17, totiente) == 1) {
        e = 17;
    }
    else if (3 < totiente && mdc(3, totiente) == 1) {
        e = 3;
    }
    else {
        e = 3;
        while (e < totiente && mdc(e, totiente) != 1) {
            e += 2;
        }
    }
    if (e >= totiente) return "ERRO";

    long long d = inversoModular(e, totiente);
    if (d < 0) return "ERRO";

    string resultado;

    if (cifrar) {
        // encripta cada caractere alfabético; mantém outros caracteres como estão
        bool first = true;
        for (char c : texto) {
            if (isalpha(static_cast<unsigned char>(c))) {
                if (!first) resultado += ' ';
                long long cif = exponenciacaoModular((long long)c, e, n);
                resultado += to_string(cif);
                first = false;
            }
            else {
                // inclui espaços ou pontuação diretamente
                resultado += c;
            }
        }
    }
    else {
        // decripta números separados por espaços
        istringstream iss(texto);
        string bloco;
        while (iss >> bloco) {
            // apenas tenta converter blocos que são inteiros
            bool digitos = true;
            for (char ch : bloco) {
                if (!isdigit(static_cast<unsigned char>(ch))) {
                    digitos = false;
                    break;
                }
            }
            if (digitos) {
                long long cif = stoll(bloco);
                long long m = exponenciacaoModular(cif, d, n);
                resultado += static_cast<char>(m);
            }
            else {
                // bloco não numérico: copia literal
                resultado += bloco;
            }
        }
    }

    return resultado;
}

int main() {
    long long p, q;
    string texto;

    if (!(cin >> p >> q)) {
        cerr << "ERRO na leitura de p e q\n";
        return 1;
    }
    cin.ignore();              // descarta newline após q
    getline(cin, texto);       // lê linha inteira de texto

    string cifrado   = rsa(texto, true,  p, q);
    string decifrado = rsa(cifrado, false, p, q);

    cout << cifrado   << "\n";
    cout << decifrado << "\n";
    return 0;
}
