    #include <iostream>
    #include <string>
    using namespace std;
    
    string cesar(string entrada){

        string codificada = "";
        for (int i = 0; i < entrada.length(); i++) {
            if (entrada[i] >= 'A' && entrada[i] <= 'Z'){
                codificada += 'A' + ((entrada[i] - 3 - 'A') % 26);
            }
            else if(entrada[i] >= 'a' && entrada[i] <= 'z'){
                    codificada += 'a' + ((entrada[i] - 3 - 'a') % 26);
                }
            else {
                codificada += entrada[i];
            }
        }
        return codificada;
    } 

    int main() {
        string entrada;
        cout << "Digite um texto para cifrar com a cifra de César:\n";
        getline(cin, entrada);

        // Exemplos para você testar digitando:
        // - Digite: ABCD        // Esperado: DEFG
        // - Digite: abcd        // Esperado: defg
        // - Digite: Cesar Cipher!  // Esperado: Fhvdu Flskhu!
        // - Digite: XYZ xyz     // Esperado: ABC abc
        // - Digite: Ola, Professor! // Esperado: Rod, Surihvvru!

        cout << "Texto cifrado: " << cesar(entrada) << endl;

    return 0;
}