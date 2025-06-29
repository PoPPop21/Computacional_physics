#include "Cuerpo.h"
#include "constantes.h" 

const double G = 1; // Constante de gravitación universal

void Cuerpo::Inicie(double m0, double R0, const Vector3d &r0, const Vector3d &V0) {
    m = m0;
    R = R0;
    r = r0;
    V = V0;
    F.setZero();
}

void Cuerpo::BorreFuerza() {
    F.setZero();
}

void Cuerpo::AdicioneFuerzaGravitacional(Cuerpo &otro) {
    Eigen::Vector3d dr = otro.r - r; // Vector de posición relativo
    double d2 = dr.squaredNorm(); // Distancia al cuadrado
    double d3 = pow(d2 + 1e-10, 1.5); // Distancia al cubo
    Vector3d fuerza = G * m * otro.m * dr / d3; // Fuerza gravitacional
    F += fuerza; // Acumula la fuerza
}

void Cuerpo::MuevaR(double dt) {
    // Actualiza la posición del cuerpo
    r += V * dt + 0.5 * F / m * dt * dt;  //Movimiento de posición

}

void Cuerpo::MuevaV(double dt,  const Vector3d &F_antes) {
    // Actualiza la velocidad del cuerpo
    V += 0.5 * (F + F_antes) / m * dt; // (Verlet)
}
