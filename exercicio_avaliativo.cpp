#include <iostream>
#include <string>
using namespace std;

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

    void primos_entre(int a, int b) {
        
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
            if (entrada[i] >= 'A' && entrada[i] <= 'Z'){
                codificada += 'A' + ((entrada[i] + 3 - 'A') % 26);
            }
            else if(entrada[i] >= 'a' && entrada[i] <= 'z'){
                    codificada += 'a' + ((entrada[i] + 3 - 'a') % 26);
                }
            else {
                codificada += entrada[i];
            }
        }
        return codificada;
    } 

    int mdc(int a, int b) {

        cout << "Caculando mdc(" << a << "," << b << ")" << endl;

        if (b == 0) {
            cout << "O mdc encontrado foi " << a << endl;
            return a;

        }
        return mdc(b, a % b);
    }

// Algoritmo de Euclides Estendido (Coeficientes de Bézout) com comentários detalhados para prova oral
// Função: calcula o mdc(a,b) e encontra inteiros x,y tais que a*x + b*y = mdc(a,b)

int bezout(int a, int b, int& x, int& y) {
    // 1. Exibir qual mdc está sendo calculado: mdc(a,b)
    cout << "Calculando mdc(" << a << "," << b << ")" << endl;

    // 2. Caso base: se b == 0, então mdc(a,0) = a, e os coeficientes são x=1, y=0
    //    Porque a*1 + b*0 = a
    if (b == 0) {
        cout << "O mdc encontrado foi " << a << endl;
        x = 1; // coeficiente para 'a'
        y = 0; // coeficiente para 'b'
        cout << "    [x=" << x << ", y=" << y << "]\n\n";
        return a;
    }

    // 3. Passo recursivo: chamar bezout trocando (a,b) por (b, a%b)
    int x1, y1;
    int mdc = bezout(b, a % b, x1, y1);

    // 4. Recalculando coeficientes para o par (a,b)
    //    Seja q = (a/b)
    //    Como (a % b) = a - q*b, substituímos:
    //      b*x1 + (a - q*b)*y1 = a*y1 + b*(x1 - q*y1)
    //    Logo:
    //      x = y1
    //      y = x1 - q*y1
    int q = a / b;
    x = y1;
    y = x1 - q * y1;

    // 5. Exibir detalhes da recomposição dos coeficientes
    cout << "Para (a=" << a << ", b=" << b << "):\n";
    cout << "  q = floor(" << a << "/" << b << ") = " << q << "\n";
    cout << "  Coeficientes retornados da recursão: x1=" << x1 << ", y1=" << y1 << "\n";
    cout << "  => x = y1 = " << y1 << "\n";
    cout << "  => y = x1 - q*y1 = " << x1 << " - " << q << "*" << y1 << " = " << y << "\n\n";

    // 6. Retornar o mdc, que permanece inalterado em todos os níveis
    return mdc;
}
/*
Notas para prova oral:
- Explique o Algoritmo de Euclides: mdc(a,b) = mdc(b, a mod b), até b=0.
- No caso base, detalhe por que x=1, y=0 satisfazem a*x + b*y = a.
- Na recursão, mostre como trocamos (a,b) por (b, a%b).
- Ao voltar da recursão, demonstre a álgebra:
    a mod b = a - q*b
    b*x1 + (a mod b)*y1 = b*x1 + (a - q*b)*y1
                       = a*y1 + b*(x1 - q*y1)
- Explique que q = floor(a/b) e que divisão inteira em C++ realiza o floor para positivos.
- Use um exemplo prático (por ex. a=30, b=21) para ilustrar cada quadro.
*/


    

    // main piso
    int main() {
    float fn;
    cin >> fn;
    cout << piso(fn) << "\n";
    }

    // main teto
    int main() {
    float fn;
    cin >> fn;
    cout << teto(fn) << "\n";
    }

    //div
    int main() {
        int a, b;
        cin >> a >> b;
        cout << meu_div(a, b) << "\n";       
    }   

    //mod
    int main() {
         int a, b;
         cin >> a >> b;
         cout << meu_mod(a, b) << "\n";
    }








    // main bezout
    int main() {
        int a, b;
        cout << "Digite a e b: ";
        cin >> a >> b;

        int x, y;
        int m = bezout(a, b, x, y);

        cout << "Resultado Final\n";
        cout << "MDC(" << a << ", " << b << ") = " << m << "\n";
        cout << "Coeficientes de Bezout: s = " << x << ", t = " << y << "\n";
        cout << a << "*" << x << " + " << b << "*" << y << " = " << m << "\n";
        return 0;
    }
    