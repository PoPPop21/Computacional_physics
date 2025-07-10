/**
* @author Angela Sofia Malagon Palmino & Jhousua Sebastian Albadan Infante
* @version No se, hicimos varias :D
* @date 2025-07-09
*/

/** @defgroup Función principal y calculo de energía.
 * @{
 */

#include <iostream>
#include <fstream>
 #include <iomanip> // setprecision
#include <vector>
#include <Eigen/Dense>
#include "Carga.h"
#include "constantes.h" 

using namespace Eigen;
using namespace std;

/**
* @brief Calcula la energía cinética y potencial del sistema de partículas.
* @param cuerpos Vector de partículas cargadas.
* @param Ek Referencia para almacenar la energía cinética total.
* @param Ep Referencia para almacenar la energía potencial total.
*/
void CalcEnergia(const vector<Cuerpo> &cuerpos, double &Ek, double &Ep, double k);

/**
* @brief Función principal que simula el movimiento de N-partículas cargadas bajo la influencia de la fuerza de Coulumb.
* @details Solicita al usuario el número de cuerpos, el paso de tiempo y el tiempo máximo de simulación.
* Luego, inicializa los cuerpos con sus respectivas propiedades y simula su interacción.
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
    * @brief Vector que almacena las partículas cargadas.
    * @details Cada cuerpo se inicializa con su carga, radio, posición y velocidad.
    * @note Se utiliza un vector de objetos Cuerpo para almacenar las propiedades de cada cuerpo
    */
    vector<Cuerpo> cuerpos(N);

    for (int i = 0; i < N; ++i) {
        double q, R, x, y, z, Vx, Vy, Vz;
        cout << "Ingrese los parámetros del cuerpo " << i + 1 << "\n ";
       
        cout << "Carga: \n";
        while (!(cin >> q) || fabs(q) < 1.602e-19  || fabs(q) > 1e3){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Valor invalido. Ingrese entre " << 1.602e-19  << " y " << 1e3 << ": \n";
        }
        cout << "Posición inicial: (x,y,z) \n";
        while (!(cin >> x >> y >> z) || fabs(x) > 1e3 || fabs(y) > 1e3 || fabs(z) > 1e3 ){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Valor invalido. Ingrese entre " << 1e3 << ": \n";
        } 
        Vector3d r(x, y, z);
        cout << "Velocidad inicial: (Vx, Vy, Vz)\n";
        while (!(cin >> Vx >> Vy >> Vz) || fabs(x) > 1e5 || fabs(y) > 1e5 || fabs(z) > 1e5 ){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Valor invalido. Ingrese entre " << 1e5 << ": \n ";
        } 
        R=1;
        Vector3d V(Vx, Vy, Vz);
        cuerpos[i].Inicie(q, R, r, V);
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
                Vector3d Fij = k * cuerpos[i].GetQ() * cuerpos[j].GetQ() * dr / d3;
                cuerpos[i].AddForce(Fij);      // Fij sobre i
                cuerpos[j].AddForce(-Fij);
            } 
        for (int i = 0; i < N; ++i) {
            cuerpos[i].MuevaV(dt, F_antes[i]); //Mover velocidades V
        }

        //Para la energía
        double Ek, Ep;
        CalcEnergia(cuerpos, Ek, Ep, k);
        energias << t << " " << Ek << " " << Ep << " " << (Ek + Ep) << "\n";

    }
    output.close();
    energias.close();
    return 0;
}
/**
* @brief Calcula la energía cinética y potencial del sistema de cuerpos.
*/
void CalcEnergia(const vector<Cuerpo> &cuerpos, double &Ek, double &Ep, double k) {
    Ek = 0;
    Ep = 0;
    int N = cuerpos.size();

    // Energía cinética
    for (const auto &c : cuerpos) {
        Vector3d v(c.GetVx(), c.GetVy(), c.GetVz());
        Ek += 0.5 * 1 * v.squaredNorm(); // masa de partícula es 1 kg
    }

    // Energía potencial eléctrica
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            Vector3d rij = cuerpos[j].GetPos() - cuerpos[i].GetPos();
            double dist = rij.norm();
            Ep -= k * cuerpos[i].GetQ() * cuerpos[j].GetQ() / (dist + 1e-10); // evitar división por cero
        }
    }
}
/** @} */ // fin del grupo
