#ifndef NRRW_H
#define NRRW_H

#include <vector>
#include <random>

class NRRW {
public:
    NRRW(int pasos, int semillas = 42);
    void realizar_caminata();
    double obtener_R2() const;

private:
    int N; // Número de pasos
    double x, y; // Posición final
    std::mt19937 generador;
    std::uniform_int_distribution<int> distribucion;

    void paso_aleatorio();
};

#endif
