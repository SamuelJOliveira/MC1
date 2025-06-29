#include <iostream>
using namespace std;

    void primos_entre(int a, int b) {
        int qntd_primos = 0;      // Conta a quantidade de primos encontrados
        int primos[1000];          // Vetor para armazenar até 100 primos encontrados

        // Garante que 'a' seja o menor e 'b' o maior
        if (a > b){
            int temp = a;
            a = b;
            b = temp;
        }

        // Percorre todos os números de a até b (inclusive)
        for (int i = a; i <= b; i++) {
            if (i < 2) continue; // Ignora números menores que 2 (não são primos)
            int contador = 0;

            // Conta os divisores de i
            for (int k = 1; k <= i; k++) {
                if (i % k == 0) {
                    contador++;
                }
            }

            // Se tiver exatamente dois divisores, é primo
            if (contador == 2) {
                primos[qntd_primos] = i; // Armazena o primo encontrado no vetor
                qntd_primos++;
            }
        }

        // Imprime os primos encontrados
        cout << "Primos entre " << a << " e " << b << ": ";
        for (int i = 0; i < qntd_primos; i++) {
            cout << primos[i] << " ";
        }
        cout << endl;
    }

    int main() {
    int a, b;
    cout << "Digite dois numeros inteiros (exemplo: 1 20): ";
    cin >> a >> b;

    primos_entre(a, b);

    // Exemplos para testar:
    // Entrada: 1 10     Esperado: 2 3 5 7
    // Entrada: 15 30    Esperado: 17 19 23 29
    // Entrada: 30 15    Esperado: 17 19 23 29 (ordem dos argumentos não importa)
    // Entrada: 1 1      Esperado: (nenhum primo)

    return 0;
}
    