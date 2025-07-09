#include "NRRW.h"
#include <cmath>

NRRW::NRRW(int pasos, int semillas)
    : N(pasos), x(0.0), y(0.0), generador(semillas), distribucion(0, 3) {
    trayectoria.clear();
    trayectoria.push_back({x, y});
}

void NRRW::realizar_caminata() {
    x = 0.0;
    y = 0.0;
    trayectoria.clear();
    trayectoria.push_back({x, y});

    for (int i = 0; i < N; ++i)
        paso_aleatorio();
}

void NRRW::paso_aleatorio() {
    int direccion = distribucion(generador);
    switch (direccion) {
        case 0: x += 1.0; break;
        case 1: x -= 1.0; break;
        case 2: y += 1.0; break;
        case 3: y -= 1.0; break;
    }
    trayectoria.push_back({x, y});
}

double NRRW::obtener_R2() const {
    return x * x + y * y;
}

const vector<pair<double, double>>& NRRW::obtener_trayectoria() const {
    return trayectoria;
}

void NRRW::guardar_trayectoria_csv(const string& filename) const {
    ofstream archivo(filename);
    archivo << "x,y\n";
    for (const auto& p : trayectoria)
        archivo << p.first << "," << p.second << "\n";
    archivo.close();
}


void NRRW::paso_aleatorio() {
    int direccion = distribucion(generador);
    switch (direccion) {
        case 0: x += 1.0; break; // derecha
        case 1: x -= 1.0; break; // izquierda
        case 2: y += 1.0; break; // arriba
        case 3: y -= 1.0; break; // abajo
    }
    trayectoria.push_back({x, y});
}

double NRRW::obtener_R2() const {
    return x*x + y*y;
}
