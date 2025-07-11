#include "../include/SistemaDosNiveles.hpp"
#include <iostream> // For debugging or messages
#include <cmath>    // For std::nan

// Constructor
SistemaDosNiveles::SistemaDosNiveles(double epsilon_val, double kBT_val)
    : epsilon(epsilon_val), kBT(kBT_val), rng(std::random_device{}()), dist(0.0, 1.0) {}

// Method to calculate exact partition function
double SistemaDosNiveles::calcularFuncionParticionExacta() const {
    // Z = e^(-E0/kBT) + e^(-E1/kBT) = 1 + exp(-epsilon/kBT)
    return 1.0 + std::exp(-epsilon / kBT);
}

// Method to calculate exact average energy
double SistemaDosNiveles::calcularEnergiaMediaExacta() const {
    // <E> = (E0*exp(-E0/kBT) + E1*exp(-E1/kBT)) / Z
    // E0=0, E1=epsilon
    double Z = calcularFuncionParticionExacta();
    return (epsilon * std::exp(-epsilon / kBT)) / Z;
}

// Method to sample a state based on Boltzmann distribution
int SistemaDosNiveles::muestrearEstado() {
    // This is a direct sampling from the Boltzmann distribution
    // P(E_0) = exp(-E_0/kBT) / Z = 1 / Z
    // P(E_1) = exp(-E_1/kBT) / Z = exp(-epsilon/kBT) / Z

    double Z = calcularFuncionParticionExacta();
    double prob_E0 = 1.0 / Z;

    double r = dist(rng); // Random number between 0 and 1

    if (r < prob_E0) {
        return 0; // State E0
    } else {
        return 1; // State E1
    }
}

// Monte Carlo simulation method
SistemaDosNiveles::ResultadosMonteCarlo SistemaDosNiveles::simularMonteCarlo(int num_pasos_mc) {
    long double sum_E = 0.0L; // Accumulator for total energy
    int count_E0 = 0;         // Count of times state E0 is sampled
    int count_E1 = 0;         // Count of times state E1 is sampled

    // Perform Monte Carlo steps
    for (int i = 0; i < num_pasos_mc; ++i) {
        int current_state = muestrearEstado(); // Sample a state

        // Accumulate energy and state counts
        if (current_state == 0) {
            // Energy for state E0 is 0
            count_E0++;
        } else {
            // Energy for state E1 is epsilon
            sum_E += epsilon;
            count_E1++;
        }
    }

    // Calculate Monte Carlo estimates after all steps
    ResultadosMonteCarlo resultados;

    // Estimate average energy: <E> = (sum of energies) / (number of steps)
    resultados.energiaMediaEstimada = static_cast<double>(sum_E / num_pasos_mc);

    // Estimate probabilities of states
    double prob_E0_mc = static_cast<double>(count_E0) / num_pasos_mc;
    // double prob_E1_mc = static_cast<double>(count_E1) / num_pasos_mc; // Not strictly needed if prob_E0_mc is known

    // Estimate partition function (Z) from estimated probabilities
    // If E0 = 0, Z = 1 / P(E0)
    if (prob_E0_mc > 0) { // Avoid division by zero
        resultados.funcionParticionEstimada = 1.0 / prob_E0_mc;
    } else {
        // Handle case where E0 is not sampled (unlikely with many steps)
        resultados.funcionParticionEstimada = std::nan(""); // Not a Number
    }

    // Return the calculated results
    return resultados;
}
