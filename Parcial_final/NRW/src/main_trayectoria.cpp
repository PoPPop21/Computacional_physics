#include <iostream>
#include <chrono> // para la hora actual
#include "NRRW.h"

using namespace std;

int main() {
    int pasos = 1000;
    unsigned semilla = chrono::system_clock::now().time_since_epoch().count();
    NRRW caminata(pasos, semilla);  // ← SEMILLA DIFERENTE CADA VEZ

    caminata.realizar_caminata();  // ← ¡No olvides generar la caminata!
    caminata.guardar_trayectoria_csv("results/trayectoria.csv");
    
    cout << "Trayectoria guardada en 'results/trayectoria.csv'\n";
    return 0;
}
