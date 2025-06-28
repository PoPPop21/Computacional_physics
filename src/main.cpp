#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#include "Cuerpo.h"

using namespace Eigen;
using namespace std;

int main() {
    int N;
    double dt, tmax;
    cout << "Ingrese el número de cuerpos: ";
    cin >> N;
    cout << "Ingrese el paso de tiempo (dt): ";
    cin >> dt;
    cout << "Ingrese el tiempo máximo (tmax): ";
    cin >> tmax;

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

    }
    output.close();
    return 0;
}