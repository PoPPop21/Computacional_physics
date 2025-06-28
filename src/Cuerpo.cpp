#include "Cuerpo.h"

const double G = 6.67430e-11; // Constante de gravitación universal

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
    double d3 = pow(d2, 1.5); // Distancia al cubo
    Vector3d fuerza = G * m * otro.m * dr / d3; // Fuerza gravitacional
    F += fuerza; // Acumula la fuerza
}

void Cuerpo::Muevase(double dt) {
    // Actualiza la velocidad y posición del cuerpo
    V += 0.5 * F / m * dt; // Actualiza la velocidad (Verlet)
    r += V * dt + 0.5 * F / m * dt * dt; // Actualiza la posición
}