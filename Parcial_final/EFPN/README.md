# Aplicación del Método de Monte Carlo a la Física Estadística 🎞🎟

Este proyecto implementa una simulación del método de Monte Carlo para un sistema simple de dos niveles de energía en el contexto de la física estadística. El objetivo es estimar la función de partición y la energía media del sistema, y comparar estos resultados con los valores teóricos exactos.

## Estructura del Proyecto 🎑

El proyecto sigue una estructura modular para facilitar la organización y el desarrollo:


proyecto_montecarlo/
├── src/
│   ├── main.cpp                 # Archivo principal del programa C++
│   └── SistemaDosNiveles.cpp    # Implementación de la clase SistemaDosNiveles
├── include/
│   ├── SistemaDosNiveles.hpp    # Definición de la clase SistemaDosNiveles
│   └── Utils.hpp                # (Opcional) Para funciones de utilidad
├── results/
│   ├── funcion_particion.dat    # Datos de la función de partición (generado por C++)
│   ├── energia_media.dat        # Datos de la energía media (generado por C++)
│   ├── funcion_particion.png    # Gráfico de la función de partición (generado por Python)
│   └── energia_media.png        # Gráfico de la energía media (generado por Python)
├── scripts/
│   └── plot_results.py          # Script de Python para la visualización de resultados
├── documents/
│   └── montecarlo.tex           # Documento principal en LaTeX (informe)
├── bin/                         # Directorio para el ejecutable compilado
├── Makefile                     # Archivo para automatizar la compilación y ejecución
└── README.md                    # Este archivo


## Teoría Implementada 🎎

El proyecto se basa en los fundamentos de la Mecánica Estadística, específicamente en el **ensamble canónico** y la **distribución de Boltzmann**.

### Sistema de Dos Niveles 🧧

Se simula un sistema simple con dos estados de energía discretos:
* **Estado Fundamental:** $E_0 = 0$
* **Estado Excitado:** $E_1 = \epsilon$ (donde $\epsilon$ es una constante positiva)

Para este sistema, las propiedades termodinámicas exactas pueden calcularse analíticamente:

* **Función de Partición ($Z$):**
    $Z = 1 + e^{-\epsilon / k_B T}$

* **Energía Media ($\langle E \rangle$):**
    $\langle E \rangle = \frac{\epsilon e^{-\epsilon / k_B T}}{1 + e^{-\epsilon / k_B T}}$

Donde $k_B$ es la constante de Boltzmann y $T$ es la temperatura.

### Método de Monte Carlo 🌻

Se utiliza una estrategia de **muestreo directo de Boltzmann** para simular el sistema:
1.  **Muestreo de Estados:** En cada paso de Monte Carlo, se selecciona un estado ($E_0$ o $E_1$) con una probabilidad directamente proporcional a su factor de Boltzmann. Esto se logra generando un número aleatorio y comparándolo con la probabilidad teórica del estado fundamental ($P_0 = 1/Z$).
2.  **Acumulación de Estadísticas:** Durante un gran número de pasos de Monte Carlo (`num_pasos_mc`), se acumula la energía total del sistema y se cuenta la frecuencia de ocupación de cada estado.
3.  **Estimación de Propiedades:**
    * **Energía Media (MC):** Se estima como el promedio de las energías muestreadas durante la simulación.
    * **Función de Partición (MC):** Se estima a partir de la probabilidad de ocupación del estado fundamental ($P_0 = \text{count\_E0} / \text{num\_pasos\_mc}$), utilizando la relación $Z = 1/P_0$.

## Compilación y Ejecución 🌼

El proyecto utiliza un `Makefile` para automatizar los procesos de compilación y ejecución. Asegúrate de tener `g++` (compilador C++) y `python3` con las librerías `numpy` y `matplotlib` instaladas en tu sistema.

Para compilar y ejecutar el proyecto, navega a la carpeta raíz del proyecto en tu terminal (`~/Computacional_physics/Parcial_final/EFPN/`) y utiliza los siguientes comandos:

1.  **Limpiar archivos generados (opcional, pero recomendado):**
    ```bash
    make clean
    make clean_results
    ```

2.  **Compilar el programa C++:**
    ```bash
    make
    ```
    Esto creará el ejecutable `montecarlo_sim` en el directorio `bin/`.

3.  **Ejecutar la simulación C++:**
    ```bash
    make run
    ```
    Este comando ejecutará el programa C++, que calculará los valores exactos y de Monte Carlo para la función de partición y la energía media a través de un rango de temperaturas. Los resultados se guardarán en archivos `.dat` dentro de la carpeta `results/`.

## Visualización de Resultados 🥗

Una vez que el programa C++ haya generado los archivos de datos, puedes usar el script de Python para plotear los resultados:

1.  **Generar los gráficos:**
    ```bash
    make plot
    ```
    Este comando ejecutará el script `scripts/plot_results.py`, que leerá los datos de `results/` y generará dos imágenes PNG (`funcion_particion.png` y `energia_media.png`) en la misma carpeta `results/`. También mostrará los gráficos en ventanas emergentes.

## Informe del Proyecto 🥓

El informe principal del proyecto se encuentra en `documents/montecarlo.tex`. Este documento debe detallar la teoría, la implementación, los resultados obtenidos y el análisis físico, incluyendo los cinco problemas sencillos adicionales mencionados en las especificaciones del proyecto.
