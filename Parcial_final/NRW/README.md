# Caminata aleatoria normalizada en 2D 🎢

Este proyecto simula múltiples caminatas aleatorias normalizadas en 2D, para valores N enteros múltiplos de 10. 

## Objetivos 🎆

- Simular múltioles caminatas aleatorias en 2D.
- Calcular el valor medio cuadrático del desplazamiento <R²>.
- Graficar ln<R²> vs. lnN.
- Ajustar una línea recta a los datos y obtener la pendiente ´a´.

## Estructura del Proyecto 🎇

- `src/`: Código fuente en C++.
- `include/`: Archivos de cabecera.
- `results/`: Archivos de salida con resultados numéricos y figuras.
- `scripts/`: Scripts de graficación (Python, Gnuplot, etc.).
- `documents/`: Informe principal en LaTeX.
- `bin/`: Ejecutables.
- `Makefile`: Compilación automatizada del proyecto.
- `README.md`: Documentación del proyecto.

## Requisitos ✨


- Compilador C++11 o superior.
- Gnuplot o Python para graficación.
- LaTeX para generación de informe.
- Doxygen (opcional) para documentación automática.

## Compilación 🎊

- Código
```bash
make

```

```bash
- Visualización de resultados 
    - python3 scripts/plot.py
    - gnuplot scripts/plot.gp
```
```bash
- Documentación 
    - make doc
