    #include <iostream>
    #include <string>
    using namespace std;

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
    