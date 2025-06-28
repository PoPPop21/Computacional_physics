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

        for (auto &c : cuerpos) c.BorreFuerza();

        for (int i = 0; i < N; i++)
            for (int j = i+1; j < N; j++) {
                cuerpos[i].AdicioneFuerzaGravitacional(cuerpos[j]);
                cuerpos[j].AdicioneFuerzaGravitacional(cuerpos[i]);
            }

        for (auto &c : cuerpos) c.Muevase(dt);
    }

    output.close();
    return 0;
}