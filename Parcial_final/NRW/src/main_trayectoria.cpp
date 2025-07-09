#include <iostream>
#include "NRRW.h"

using namespace std;

int main() {
    int pasos = 1000;
    NRRW caminata(pasos, 123); // Semilla fija para reproducibilidad
    caminata.realizar_caminata();

    caminata.guardar_trayectoria_csv("results/trayectoria.csv");
    cout << "Trayectoria guardada en 'results/trayectoria.csv'" << endl;

    return 0;
}
