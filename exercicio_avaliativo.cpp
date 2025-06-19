#include <iostream>
#include <string>
using namespace std;

// todas as suas funções aqui...
/*
int piso(float n){
    int k;
    if (n >= 0){
    k = 0;
    bool achou_piso = false;

        while (!achou_piso){

            if (k <= n && k+1 > n){
                achou_piso = true;
            } else {
                k++;
            }
        }
        if (achou_piso){
            return k;
        }
    }
    else {
        k = -1;
        bool achou_piso = false;
        while (!achou_piso){

            if (k <= n && k+1 > n){
                achou_piso = true;
            } else {
                k--;
            }
        }
        if (achou_piso){
            return k;
        }
    }
    return k;
*/

    int piso(float n) {
    int k = (n >= 0) ? 0 : -1;

    while (!(k <= n && k + 1 > n)) {
        k += (n >= 0) ? 1 : -1;
    }

    return k;
}


int teto(float n){
    int k = (n >= 0) ? 0 : -1;

    while (!(k <= n && k-1 < n)){
        k += (n >= 0) ? 1 : -1;
    }    
    
    return k;
}

//int div(int a, int b;) {
 /*
 int q, r;
    q = ((a > 0 && b < 0) || (a < 0 && b > 0)) ? -1 : 0;

    r = -1;

    int modulo_b;

    modulo_b = (b < 0) ? -b : b;

    while (!( (a == b * q + r) && (0 <= r && r < modulo_b) )){
        q += ((a > 0 && b < 0) || (a < 0 && b > 0)) ? -1 : 1;
        r = a - (b * q);
    }

    return q;
 */   

    int meu_div(int a, int b) {

        if (b == 0) {
            cout << "Erro: divisor igual a zero.\n";
            return 0; 
        }

        // Valor absoluto de b 
        int modulo_b = (b < 0) ? -b : b;

        int q = 0; // se o while quebrar na primeira iteracao significa que o A e 0
        int r;

        while (true) {
            r = a - b * q;

            if (r >= 0 && r < modulo_b) {
                break;
            }

            // Anda na direção correta com base no sinal de a * b
            if (a * b < 0) {
                q = q - 1;
            } else {
                q = q + 1;
            }
        }

        return q;
    }

    int meu_mod(int a, int b) {
        int q = meu_div(a, b);
        return a - b * q;
    }

    int primos_entre(int a, int b) {
        
        int qntd_primos = 0;
        
        int primos[100];

        if (a < b){
            int temp = b;
            b = a;
            a = temp;
        }

        for (int i = a; i <= b; i++){
            int contador = 0;

            for (int k = 1; k <= i; k++){
                if (i % k == 0){
                    contador++;
                }
            }
            if (contador == 2){
                primos[qntd_primos] = i;
                qntd_primos++;
            }
        }
    // Imprimir os primos encontrados
    cout << "Primos entre " << a << " e " << b << ": ";
    for (int i = 0; i < qntd_primos; i++) {
        cout << primos[i] << " ";
    }
    cout << endl;
}
    
    string cesar(string entrada){
        string codificada = "";
        for (int i = 0; i < entrada.length(); i++) {
            codificada = ((entrada[i] + '3' - entrada[i]) + 1) % 26;
        } 
        return codificada;
    } 
