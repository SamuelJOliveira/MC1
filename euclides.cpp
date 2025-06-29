    #include <iostream>
    #include <string>
    using namespace std;

    int mdc(int a, int b) {

        cout << "Caculando mdc(" << a << "," << b << ")" << endl;

        if (b == 0) {
            cout << "O mdc encontrado foi " << a << endl;
            return a;

        }
        return mdc(b, a % b);
    }

    int main() {
        int a, b;

        // Solicita ao usuário para digitar dois números inteiros
        cout << "Digite o primeiro numero: ";
        cin >> a;
        cout << "Digite o segundo numero: ";
        cin >> b;

        // Calcula e mostra o resultado do mdc
        int resultado = mdc(a, b);
        cout << "O mdc de " << a << " e " << b << " eh: " << resultado << endl;

        // Exemplos para testar (digite estes pares de números quando solicitado):
        // 30 e 21   (esperado: 3)
        // 100 e 25  (esperado: 25)
        // 17 e 13   (esperado: 1)
        // 12 e 0    (esperado: 12)
        
        return 0;
}