/**
* @author Angela Sofia Malagon Palmino & Jhousua Sebastian Albadan Infante
* @version No se, hicimos varias :D
* @date 2025-07-03
*/

/** @defgroup Función principal y calculo de energía.
 * @{
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#include "Cuerpo.h"
#include "constantes.h" 

using namespace Eigen;
using namespace std;

/**
* @brief Calcula la energía cinética y potencial del sistema de cuerpos.
* @param cuerpos Vector de cuerpos celestes.
* @param Ek Referencia para almacenar la energía cinética total.
* @param Ep Referencia para almacenar la energía potencial total.
*/
void CalcEnergia(const vector<Cuerpo> &cuerpos, double &Ek, double &Ep, double G);

/**
* @brief Función principal que simula el movimiento de N cuerpos celestes bajo la influencia de la gravedad.
* @details Solicita al usuario el número de cuerpos, el paso de tiempo y el tiempo máximo de simulación.
* Luego, inicializa los cuerpos con sus respectivas propiedades y simula su
*/

int main() {
    int N;
    double dt, tmax;
    cout << "Ingrese el número de cuerpos: ";
    cin >> N;
    cout << "Ingrese el paso de tiempo (dt): ";
    cin >> dt;
    cout << "Ingrese el tiempo máximo (tmax): ";
    cin >> tmax;

    /**
    * @brief Vector que almacena los cuerpos celestes.
    * @details Cada cuerpo se inicializa con su masa, radio, posición y velocidad.
    * @note Se utiliza un vector de objetos Cuerpo para almacenar las propiedades de cada cuerpo
    */
    vector<Cuerpo> cuerpos(N);
    for (int i = 0; i < N; ++i) {
        double m, R, x, y, z, Vx, Vy, Vz;
        cout << "Ingrese los parámetros del cuerpo " << i + 1 << " (m R x y z Vx Vy Vz): ";
        cin >> m >> R >> x >> y >> z >> Vx >> Vy >> Vz;
        Vector3d r(x, y, z);
        Vector3d V(Vx, Vy, Vz);
        cuerpos[i].Inicie(m, R, r, V);
    }

    ofstream output("results/datosN.dat");
    ofstream energias("results/energiasN.dat");

    /**
    * @brief inicializa el archivo de salida con los encabezados.
    * @details El archivo contiene el tiempo, las posiciones y velocidades de cada cuerpo.
    * @note Se utiliza un formato específico para almacenar los datos de cada cuerpo en cada paso
    * de tiempo.
    */
     for (double t = 0; t <= tmax; t += dt) {
        output << t;
        for (auto &c : cuerpos)
            output << " " << c.Getx() << " " << c.Gety() << " " << c.Getz()
                    << " " << c.GetVx() << " " << c.GetVy() << " " << c.GetVz();
        output << "\n";
     
        for (auto &c : cuerpos) c.MuevaR(dt); //Mover posiciones r

        vector<Vector3d> F_antes(N);
        for (int i = 0; i < N; ++i)
            F_antes[i] = cuerpos[i].GetF();

        for (auto &c : cuerpos) c.BorreFuerza();
        for (int i=0; i < N; ++i) 
            for (int j = i+1; j < N; ++j) {
                Vector3d dr = cuerpos[j].GetPos() - cuerpos[i].GetPos();
                double d2 = dr.squaredNorm();
                double d3 = pow(d2 + 1e-10, 1.5); 
                Vector3d Fij = G * cuerpos[i].GetM() * cuerpos[j].GetM() * dr / d3;
                cuerpos[i].AddForce(Fij);      // Fij sobre i
                cuerpos[j].AddForce(-Fij);
            } 
        for (int i = 0; i < N; ++i) {
            cuerpos[i].MuevaV(dt, F_antes[i]); //Mover velocidades V
        }

        //Para la energía
        double Ek, Ep;
        CalcEnergia(cuerpos, Ek, Ep, G);
        energias << t << " " << Ek << " " << Ep << " " << (Ek + Ep) << "\n";

    }
    output.close();
    energias.close();
    return 0;
}
/**
* @brief Calcula la energía cinética y potencial del sistema de cuerpos.
*/
void CalcEnergia(const vector<Cuerpo> &cuerpos, double &Ek, double &Ep, double G) {
    Ek = 0;
    Ep = 0;
    int N = cuerpos.size();

    // Energía cinética
    for (const auto &c : cuerpos) {
        Vector3d v(c.GetVx(), c.GetVy(), c.GetVz());
        Ek += 0.5 * c.GetM() * v.squaredNorm();
    }

    // Energía potencial gravitacional
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            Vector3d rij = cuerpos[j].GetPos() - cuerpos[i].GetPos();
            double dist = rij.norm();
            Ep -= G * cuerpos[i].GetM() * cuerpos[j].GetM() / (dist + 1e-10); // evitar división por cero
        }
    }
}
/** @} */ // fin del grupo
