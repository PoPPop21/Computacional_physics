#include <iostream>
#include "NRRW.h"

using namespace std;

int main() {
    int pasos = 100;
    NRRW caminata(100, 42);


    for(int i = 0; i < pasos; ++i)
        caminata.paso_aleatorio();

    caminata.guardar_trayectoria_csv("results/trayectoria.csv");
    return 0;
}
