#ifndef CUERPO_H
#define CUERPO_H

#include <Eigen/Dense>
using namespace Eigen;

/**
* Clase que representa un cuerpo celeste en el sistema gravitacional.
*/

class Cuerpo {
private:
    double m, R;
    Vector3d r, V, F; // Posición, velocidad y fuerza del cuerpo

public:
    void Inicie(double m0, double R0, const Vector3d &r0, const Vector3d &V0);
    Vector3d GetF() const { return F; }
    void BorreFuerza();
    void AdicioneFuerzaGravitacional(Cuerpo &otro);
    void MuevaR(double dt);
    void MuevaV(double dt, const Vector3d &F_antes);

    // Getters
    double Getx() const { return r.x(); }
    double Gety() const { return r.y(); }
    double Getz() const { return r.z(); }

    double GetVx() const { return V.x(); }
    double GetVy() const { return V.y(); }
    double GetVz() const { return V.z(); }

    double GetM() const { return m; }
    double GetR() const { return R; }
};

#endif // CUERPO_H
