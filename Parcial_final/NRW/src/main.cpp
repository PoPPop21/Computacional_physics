#include <iostream>
#include <fstream>
#include <cmath>
#include "NRRW.h"

using namespace std;

int main() {
    vector<int> pasos = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
    int repeticiones = 1000;

    ofstream archivo("../results/data.csv");
    archivo << "lnN,ln<R2>\n";

    for (int N : pasos) {
        double suma_R2 = 0.0;
        for (int i = 0; i < repeticiones; ++i) {
            NRRW caminata(N, i);
            caminata.realizar_caminata();
            suma_R2 += caminata.obtener_R2();
        }
        double promedio = suma_R2 / repeticiones;
        archivo << log(N) << "," << log(promedio) << "\n";
        cout << "N = " << N << " completado\n";
    }

    archivo.close();
    return 0;
}
