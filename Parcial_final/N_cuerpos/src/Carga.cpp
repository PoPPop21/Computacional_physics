/**
* @author Angela Sofia Malagon Palmino & Jhousua Sebastian Albadan Infante
* @version No se, hicimos varias :D
* @date 2025-07-03
*/

/** @defgroup SimulacionElectrica Clases para simular partículas cargadas Cuerpo.cpp
 * @{
 */

#include "Carga.h"
#include "constantes.h" 
/**
* @brief Inicializa el cuerpo con carga, radio, posición y velocidad.
*/

void Cuerpo::Inicie(double q0, double R0, const Vector3d &r0, const Vector3d &V0) {
    q = q0;
    R = R0;
    r = r0;
    V = V0;
    F.setZero();
}
/**
* @brief Devuelve la fuerza neta actuando sobre el cuerpo.
*/
void Cuerpo::BorreFuerza() {
    F.setZero();
}
/**
* @brief Calcula y añade la fuerza eléctrica de otro cuerpo.
* @param otro Otro cuerpo cargado del cual se calculará la fuerza eléctrica.
* @details Utiliza la ley de Coulomb para calcular la fuerza entre dos cuerpos.
* La fuerza se acumula en el vector de fuerza del cuerpo actual.
* Se evita la división por cero añadiendo un pequeño valor (1e-10)
* a la distancia al cuadrado antes de calcular la distancia al cubo.
*/
void Cuerpo::AdicioneFuerzaElectrica(Cuerpo &otro) {
    Eigen::Vector3d dr = otro.r - r; // Vector de posición relativo
    double d2 = dr.squaredNorm(); // Distancia al cuadrado
    double d3 = pow(d2 + 1e-10, 1.5); // Distancia al cubo
    Vector3d fuerza = k * q * otro.q * dr / d3; // Fuerza gravitacional
    F += fuerza; // Acumula la fuerza
}
/**
* @brief Actualiza la posición del cuerpo según su velocidad y la fuerza neta.
* @param dt Paso de tiempo para la actualización de la posición.
* @details Utiliza la ecuación de movimiento para actualizar la posición del cuerpo.
*/
void Cuerpo::MuevaR(double dt) {
    // Actualiza la posición del cuerpo
    r += V * dt + 0.5 * F / 1 * dt * dt;  //Movimiento de posición, suponemos que el cuerpo tiene masa de 1kg

}
/**
* @brief Actualiza la velocidad del cuerpo usando el método de Verlet.
* @note Este método utiliza la fuerza neta actual y la fuerza neta del paso anterior para actualizar la velocidad.
* @note El método de Verlet es un método numérico que permite una mejor conservación de la energía en sistemas dinámicos.
*/
void Cuerpo::MuevaV(double dt,  const Vector3d &F_antes) {
    // Actualiza la velocidad del cuerpo
    V += 0.5 * (F + F_antes) / 1 * dt; // (Verlet)
}

/** @} */ // fin del grupo

