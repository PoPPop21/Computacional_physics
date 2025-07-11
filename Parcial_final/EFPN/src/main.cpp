#include <iostream>
#include <fstream>
#include "../include/SistemaDosNiveles.hpp"

using namespace std;

int main() {
    double epsilon;
    double kbt_min, kbt_max;
    int num_puntos_kbt;
    int num_pasos_mc;

    cout << "Bienvenido al simulador del sistema de dos niveles." << endl;
    cout << "Por favor, ingrese los siguientes parametros:" << endl;
    cout << "Ingrese el valor de epsilon (energia del segundo nivel): ";
    cin >> epsilon;
    cout << "Ingrese el valor minimo de kBT: ";
    cin >> kbt_min;
    cout << "Ingrese el valor maximo de kBT: ";
    cin >> kbt_max;
    cout << "Ingrese el numero de puntos de kBT: ";
    cin >> num_puntos_kbt;
    cout << "Ingrese el numero de pasos de Monte Carlo: ";
    cin >> num_pasos_mc;    

    ofstream outfile_Z("results/funcion_particion.dat");
    ofstream outfile_E("results/energia_media.dat");

    if (!outfile_Z.is_open() || !outfile_E.is_open()) {
        cerr << "Error: No se pudieron abrir los archivos de resultados." << endl;
        return 1;
    }

    for (int i = 0; i < num_puntos_kbt; ++i) {
        double kBT = kbt_min + (kbt_max - kbt_min) * i / (num_puntos_kbt - 1);

        SistemaDosNiveles sistema(epsilon, kBT);

        // Calcular valores exactos
        double Z_exacto = sistema.calcularFuncionParticionExacta();
        double E_exacto = sistema.calcularEnergiaMediaExacta();

        // Simular con Monte Carlo
        SistemaDosNiveles::ResultadosMonteCarlo resultados_mc = sistema.simularMonteCarlo(num_pasos_mc);

        outfile_Z << kBT << "\t" << Z_exacto << "\t" << resultados_mc.funcionParticionEstimada << endl;
        outfile_E << kBT << "\t" << E_exacto << "\t" << resultados_mc.energiaMediaEstimada << endl;
    }

    outfile_Z.close();
    outfile_E.close();

    cout << "Resultados guardados en results/funcion_particion.dat y results/energia_media.dat" << endl;

    return 0;

}