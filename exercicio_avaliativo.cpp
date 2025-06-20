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

    int bezout(int a, int b, int& x, int& y){

        cout << "Caculando mdc(" << a << "," << b << ")" << endl;

        if (b == 0){
            cout << "O mdc encontrado foi " << a << endl;
            x = 1;
            y = 0;
            cout << "    [x=" << x << ", y=" << y << "]\n\n";
            return a;
        }

        int x1, y1;

        int mdc = bezout(b, a % b, x1, y1);

        x = y1;
        y = x1 - (a / b) * y1;
                                    //b x1 + (a%b) y1 = mdc
                                    //a x + b y = mdc
                                    // b x1 + (a - a/b * b) y1 = mdc
                                    // b x1 + a * y1 - a/b * b * y1 = mdc
                                    // a * y1 + b (x1 * -a/b * y1) = a x + b y 
                                    // x = y1 --- y = (x1 * -a/b * y1)

        cout << "Para (a=" << a << ", b=" << b << "):\n";
        cout << "x = y1 = " << y1 << "\n";
        cout << "y = x1 - (a/b)*y1 = " << x1 << " - (" << a << "/" << b << ")*" << y1 << " = " << y << "\n\n";

        return mdc;
    }


    

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
    