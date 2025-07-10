#ifndef SISTEMADOSNIVELES_HPP
#define SISTEMADOSNIVELES_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include <random> // para generar numeros aleatorios 

using namespace std;

class SistemaDosNiveles {
private:
    double epsilon; // Energia del segundo nivel
    double kBT; // Energia termica 

    mt19937 rng; // Generador de numeros aleatorios
    uniform_real_distribution<double> dist; // Distribucion uniforme

public:
// Constructor 
    SistemaDosNiveles(double epsilon_val, double kBT_val)

    // Métodos para calcular propiedades exactas
    double calcularFuncionParticionExacta() const;
    double calcularEnergiaMediaExacta() const;

    struct ResultadosMonteCarlo {
        double funcionParticionEstimada;
        double energiaMediaEstimada;
    };

    ResultadosMonteCarlo simularMonteCarlo(int num_pasos_mc);

    private:
    // Metodos auxiliares si son necesarios para el MC
    int muestrearEstado();
};

#endif // SISTEMADOSNIVELES_HPP