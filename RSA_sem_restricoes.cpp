#include <iostream>
#include <string>
using namespace std;

// 1) Teste de primalidade: trial division contando divisores
bool ehPrimo(long long n)
{
    if (n < 2) {
        return false;
    }

    int count = 0;

    for (long long i = 1; i <= n; ++i){
        if (n % i == 0) {
            ++count;
        }
    }       

    return count == 2;
}

// 2) Algoritmo de Euclides para gcd(a,b)
long long mdc(long long a, long long b)
{
    return b == 0 ? a : mdc(b, a % b);
}

// 3) Euclides estendido: encontra x,y tais que a*x + b*y = gcd(a,b)
long long bezout(long long a, long long b, long long &x, long long &y)
{
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

// 4) Inverso modular
long long inversoModular(long long a, long long m) // Teste 1: a = 3, m = 11 → inverso esperado = 4
{
    long long x, y;
    long long g = bezout(a, m, x, y);
    return (x % m + m); //exemplo para ser testado x = 14 e m = 5 x = -3 m = 5
}

// 5) Expoção modular ingênua
long long exponenciacaoModular(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;
    for (long long i = 0; i < exp; ++i)
        res = (res * base) % mod;
    return res;
}

// 6) RSA: cifrar=true para encriptar, false para decriptar
string rsa(const string &texto, bool cifrar, long long p, long long q)
{
    if (!ehPrimo(p) || !ehPrimo(q) || p == q)
        return "ERRO";

    long long n = p * q;
    long long totiente = (p - 1) * (q - 1);

    // escolhe e ímpar e coprimo
    long long e = 3;
    while (e < totiente && mdc(e, totiente) != 1)
        e += 2;

    long long d = inversoModular(e, totiente);
    if (d < 0)
        return "ERRO";

    if (cifrar)
    {
        // Cifra todos os caracteres ASCII (0–255)
        string codificado;
        for (size_t i = 0; i < texto.length(); ++i) {
            unsigned char ch = texto[i]; //garante que vai de 0 a 255
            int m = int(ch);                       // 0…255
            long long c = exponenciacaoModular(m, e, n);
            codificado += to_string(c);
            codificado += ' ';
        }
        return codificado;
    }
    else
    {
        // Decodifica a sequência de números (separados por espaço)
        string decodificado;
        string bloco;
        size_t i = 0;
                while (i < texto.length()) {
            if (texto[i] == ' '){
                 ++i;
                 continue;
                }
            bloco.clear();
            while (i < texto.length() && texto[i] != ' '){
                bloco += texto[i++];
                long long c = stoll(bloco);
                long long m = exponenciacaoModular(c, d, n);
                decodificado += char(m);

            }
        }
        return decodificado;
    }
}

int main()
{
    long long p, q;
    cout << "Digite dois numeros primos p e q: ";
    cin >> p >> q;
    cin.ignore();  // consome '\n'

    string mensagem;
    cout << "Mensagem para cifrar: ";
    getline(cin, mensagem);

    // Criptografa
    string cifrado = rsa(mensagem, true, p, q);
    if (cifrado == "ERRO") {
        cerr << "Erro nos parametros.\n";
        return 1;
    }
    cout << "Texto cifrado: " << cifrado << "\n";

    // Descriptografa
    string decifrado = rsa(cifrado, false, p, q);
    if (decifrado == "ERRO") {
        cerr << "Erro ao decifrar.\n";
        return 1;
    }
    cout << "Texto decifrado: " << decifrado << "\n";

    return 0;
}
