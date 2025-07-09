#include "NRRW.h"
#include <cmath>

NRRW::NRRW(int pasos, int semillas)
    : N(pasos), x(0.0), y(0.0), generador(semillas), distribucion(0, 3) {}

void NRRW::realizar_caminata() {
    x = 0.0; y = 0.0;
    for (int i = 0; i < N; ++i)
        paso_aleatorio();
}

void NRRW::paso_aleatorio() {
    int direccion = distribucion(generador);
    switch (direccion) {
        case 0: x += 1.0; break; // derecha
        case 1: x -= 1.0; break; // izquierda
        case 2: y += 1.0; break; // arriba
        case 3: y -= 1.0; break; // abajo
    }
}

double NRRW::obtener_R2() const {
    return x*x + y*y;
}
