/**
* @author Angela Sofia Malagon Palmino & Jhousua Sebastian Albadan Infante
* @version No se, hicimos varias :D
* @date 2025-07-03
*/
#ifndef CUERPO_H
#define CUERPO_H

#include <Eigen/Dense>
#include <vector>
using namespace Eigen;
using std::vector;

/**
* @class Cuerpo
* @brief Representa un cuerpo celeste en un sistema gravitacional.
*/

class Cuerpo {
/**
* Private:
* @param m Masa del cuerpo.
* @param R Radio del cuerpo.
* @param r Vector3d que representa la posición del cuerpo.
* @param V Vector3d que representa la velocidad del cuerpo.
* @param F Vector3d que representa la fuerza neta actuando sobre el cuerpo.
*/
private:
    double m, R;
    Vector3d r, V, F; // Posición, velocidad y fuerza del cuerpo
/**
* Public:
* @brief Métodos para inicializar el cuerpo, calcular fuerzas, mover posiciones y velocidades.
* @details
* Inicie: Inicializa el cuerpo con masa, radio, posición y velocidad.
* GetF: Devuelve la fuerza neta actuando sobre el cuerpo.
* BorreFuerza: Resetea la fuerza neta a cero.
* AdicioneFuerzaGravitacional: Calcula y añade la fuerza gravitacional de otro cuerpo.
* MuevaR: Actualiza la posición del cuerpo según su velocidad y la fuerza neta.
* MuevaV: Actualiza la velocidad del cuerpo usando el método de Verlet.
* Getx, Gety, Getz: Devuelven las coordenadas x, y, z de la posición del cuerpo.
* GetVx, GetVy, GetVz: Devuelven las componentes de la velocidad del cuerpo.
* GetM: Devuelve la masa del cuerpo.
* GetR: Devuelve el radio del cuerpo.
* AddForce: Añade una fuerza adicional al cuerpo.
* GetPos: Devuelve la posición del cuerpo como un Vector3d.
* @note Las fuerzas se calculan en unidades el sistema internacional, y la constante G se define en constantes.h.
*/
public:
    void Inicie(double m0, double R0, const Vector3d &r0, const Vector3d &V0);
    Vector3d GetF() const { return F; }
    void BorreFuerza();
    void AdicioneFuerzaGravitacional(Cuerpo &otro);
    void MuevaR(double dt);
    void MuevaV(double dt, const Vector3d &F_antes);
    //Calculamos la energía
    // Getters
    double Getx() const { return r.x(); }
    double Gety() const { return r.y(); }
    double Getz() const { return r.z(); }

    double GetVx() const { return V.x(); }
    double GetVy() const { return V.y(); }
    double GetVz() const { return V.z(); }

    double GetM() const { return m; }
    double GetR() const { return R; }
    void AddForce(const Vector3d &f) { F += f; }
    Vector3d GetPos() const { return r; }
    

};

#endif // CUERPO_H
