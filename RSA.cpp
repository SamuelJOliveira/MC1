#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// 1) Teste de primalidade: trial division contando divisores
bool ehPrimo(long long n)
{
    if (n < 2)
        return false;
    int count = 0;
    for (long long i = 1; i <= n; ++i)
    {
        if (n % i == 0)
            ++count;
    }
    return count == 2; // só 1 e n dividem
}

// 2) Algoritmo de Euclides para gcd(a,b)
long long mdc(long long a, long long b)
{
    return b == 0 ? a : mdc(b, a % b);
}

// 3) Euclides estendido: encontra x,y tais que a*x + b*y = gcd(a,b)
long long bezout(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
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
long long inversoModular(long long a, long long m)
{
    long long x, y;
    long long g = bezout(a, m, x, y);
    return (x % m + m);
}

// 5) Expoção modular: calcula (base^exp) mod mod
long long exponenciacaoModular(long long base, long long exp, long long mod) // 3 . 3 . 3 . 3 ai dps  9 . 3 . 3  ai dps  4 . 3 . 3
{
    long long res = 1;
    base = base % mod;
    for (long long i = 0; i < exp; ++i)
    {
        res = (res * base) % mod;   // base = 3, exp = 4, mod = 5
    }
    return res;
}

// 6) RSA: cifrar=true para encriptar, false para decriptar
string rsa(const string &texto, bool cifrar, long long p, long long q)
{
    if (!ehPrimo(p) || !ehPrimo(q) || p == q)
    {
        return "ERRO";
    }

    long long n = p * q;
    long long totiente = (p - 1) * (q - 1);

    // escolhe e padrão se coprimo, senão busca próximo ímpar
    long long e = 3; // nao pode ser 1 pois, a mensagem nao codificariatem // comecamos do e = 2 pq geralmente phi é par entao eu so pego os impares
    while (e < totiente && mdc(e, totiente) != 1)
    {
        e += 2;
    }

    long long d = inversoModular(e, totiente); // e . d = 1 mod tot
    if (d < 0)
        return "ERRO";

    string resultado = "";
    string codificado = "";

    if (cifrar)
    {
        // mapeia A→00…Z→25
        for (int i = 0; i < (int)texto.length(); i++) {
            int ch = texto[i];
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch - 'A';
                if (ch >= 0 && ch <= 9) {
                    string s = "0";
                    s = s + char('0' + ch);
                    resultado = resultado + s;
                }
                else {
                    resultado = resultado + to_string(ch);
                }
            }
            else if (ch >= 'a' && ch <= 'z') {
                ch = ch - 'a';
                if (ch >= 0 && ch <= 9) {
                    string s = "0";
                    s = s + char('0' + ch); // esse 0 serve para transformar no correspondente na tabela ascii. 48 é o 0
                    resultado = resultado + s;
                }
                else {
                    resultado = resultado + to_string(ch);
                }
            }
        }
        // cifra cada par de dígitos
        for (int pos = 0; pos < resultado.length(); pos += 2) {
            int m = (resultado[pos] - '0') * 10 + (resultado[pos+1] - '0');
            long long c = exponenciacaoModular(m, e, n);
            codificado = codificado + to_string(c) + ' ';
        }

        return codificado;
    }
    else
    {
        // decodificação: texto contém valores cifrados separados por espaço
        string decodificado = "";
        string bloco;
        size_t i = 0;

        while (i < texto.length()) {
            // pula espaços
            if (texto[i] == ' ') {
                ++i;
                continue;
            }
            // lê o próximo número cifrado
            bloco.clear();
            while (i < texto.length() && texto[i] != ' ') {
                bloco += texto[i++];
            }
            long long c = stoll(bloco); //stoll para tranformar string em long long
            // recupera m = c^d mod n
            long long m = exponenciacaoModular(c, d, n); // teorema chines dos restos garante uma solucao unica
            // converte 0→'A', 1→'B', …, 25→'Z'
            decodificado += char('A' + m); // se m = 1 a letra e b;
        }

        return decodificado;
    }
}

int main() { //p e q = 61 53 e texto: HELLO
    long long p, q;
    cout << "Digite dois numeros primos p e q: ";
    cin >> p >> q;
    cin.ignore();  // descarta o '\n' antes de ler a mensagem

    string mensagem;
    cout << "Mensagem (A ate Z) para cifrar: ";
    getline(cin, mensagem);

    // 1) Criptografa
    string cifrado = rsa(mensagem, true, p, q);
    if (cifrado == "ERRO") {
        cout << "Erro ao gerar chave ou parametros invalidos.\n";
        return 1;
    }
    cout << "Texto cifrado: " << cifrado << "\n";

    // 2) Descriptografa
    string decifrado = rsa(cifrado, false, p, q);
    if (decifrado == "ERRO") {
        cout << "Erro na decodificacao.\n";
        return 1;
    }
    cout << "Texto decifrado: " << decifrado << "\n";

    return 0;
}