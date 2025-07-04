   #include <iostream>
   using namespace std;
   
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

            // Anda na direção correta com base no sinal de a * b para nao ficar em loop infinito e atingir a condicao de quebra
            // para que o resto esteja entre o 0 e o modulo de b;
            if (a * b < 0) {
                q = q - 1;
            } else {
                q = q + 1;
            }
        }

        return q;
    }

     //div
    int main() {
        int a, b;
        cin >> a >> b;
        cout << meu_div(a, b) << "\n";       
    }   
