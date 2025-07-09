#ifndef NRRW_H
#define NRRW_H

#include <vector>
#include <random>
#include <string> // Para std::string
#include <utility> // Para std::pair
#include <fstream>

using namespace std;

class NRRW {
public:
    NRRW(int pasos, int semillas = 42);
    void realizar_caminata();
    double obtener_R2() const;
    
    const vector<pair<double, double>>& obtener_trayectoria() const;
    void guardar_trayectoria_csv(const string& filename) const;

private:
    int N; // Número de pasos
    double x, y; // Posición actual
    mt19937 generador;
    uniform_int_distribution<int> distribucion;

    vector<pair<double, double>> trayectoria;

    void paso_aleatorio();
};

#endif
