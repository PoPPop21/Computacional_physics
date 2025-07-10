#include "../include/SistemaDosNiveles.hpp"
#include <iostream> 

SistemaDosNiveles::SistemaDosNiveles(double epsilon_val, double kBT_val)
    : epsilon(epsilon_val), kBT(kBT_val), rng(std::random_device{}()), dist(0.0, 1.0) {}

double SistemaDosNiveles::calcularFuncionParticionExacta() const {
    // Z = e^(-E0/kBT) + e^(-E1/kBT) = 1 + exp(-epsilon/kBT)
    return 1.0 + std::exp(-epsilon / kBT);
}

double SistemaDosNiveles::calcularEnergiaMediaExacta() const {
    // <E> = (E0*exp(-E0/kBT) + E1*exp(-E1/kBT)) / Z
    // E0=0, E1=epsilon
    double Z = calcularFuncionParticionExacta();
    return (epsilon * std::exp(-epsilon / kBT)) / Z;
}

int SistemaDosNiveles::muestrearEstado() {
    // Este es un muestreo directo de la distribucion de Boltzmann
    // P(E_0) = exp(-E_0/kBT) / Z = 1 / Z
    // P(E_1) = exp(-E_1/kBT) / Z = exp(-epsilon/kBT) / Z

    double Z = calcularFuncionParticionExacta();
    double prob_E0 = 1.0 / Z;
    // double prob_E1 = std::exp(-epsilon / kBT) / Z; // no es estrictamente necesario calcularla

    double r = dist(rng); // Numero aleatorio entre 0 y 1

    if (r < prob_E0) {
        return 0; // Estado E0
    } else {
        return 1; // Estado E1
    }
}

SistemaDosNiveles::ResultadosMonteCarlo SistemaDosNiveles::simularMonteCarlo(int num_pasos_mc) {
    long double sum_exp_beta_E = 0.0L; // Para Z
    long double sum_E = 0.0L;         // Para <E>
    long double current_energy = 0.0L; // Energia del estado actual
    int current_state = 0; // Iniciar en el estado 0

    // Para la estimacion de Z y <E> por muestreo directo,
    // simplemente generamos muchos estados y promediamos
    // los valores de exp(-E/kBT) y E.

    for (int i = 0; i < num_pasos_mc; ++i) {
        // Muestrea un estado
        current_state = muestrearEstado();

        // Determina la energia del estado muestreado
        if (current_state == 0) {
            current_energy = 0.0L;
        } else {
            current_energy = epsilon;
        }

        // Acumulamos energia para la energia media
        sum_E += current_energy;

        // Calculo de las estimaciones
        ResultadosMonteCarlo resultados;
        resultados.energiaMediaEstimada = static_cast<double>(sum_E / num_pasos_mc);

        int count_E0 = 0;
    int count_E1 = 0;
    for (int i = 0; i < num_pasos_mc; ++i) {
        if (muestrearEstado() == 0) {
            count_E0++;
        } else {
            count_E1++;
        }
    }
    double prob_E0_mc = static_cast<double>(count_E0) / num_pasos_mc;
    // double prob_E1_mc = static_cast<double>(count_E1) / num_pasos_mc;

    // Si E0 = 0, Z = 1 / P(E0)
    // Si E1 = epsilon, Z = exp(-epsilon/kBT) / P(E1)
    // Ambas deben dar el mismo Z.
    if (prob_E0_mc > 0) { // Evitar division por cero
        resultados.funcionParticionEstimada = 1.0 / prob_E0_mc;
    } else {
        // Manejar caso donde no se muestreo E0 (poco probable con muchos pasos)
        resultados.funcionParticionEstimada = std::nan(""); // Not a Number
    }

    // Recalcular energia media basada en las probabilidades estimadas
    // <E> = E0*P(E0) + E1*P(E1) = 0*P(E0) + epsilon*P(E1)
    resultados.energiaMediaEstimada = epsilon * (static_cast<double>(count_E1) / num_pasos_mc);


    return resultados;
}
