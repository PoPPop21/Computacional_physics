import numpy as np
import matplotlib.pyplot as plt

# Cargar datos
data = np.loadtxt("resultados/datosN.dat")
t = data[:, 0]

# Número de cuerpos (asume 6 columnas por cuerpo: x, y, z, vx, vy, vz)
n_columnas = data.shape[1] - 1
N = n_columnas // 6

# Graficar trayectoria (x vs y) de cada cuerpo
for i in range(N):
    xi = data[:, 1 + i*6]
    yi = data[:, 2 + i*6]
    plt.plot(xi, yi, label=f"Cuerpo {i+1}")

plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Trayectorias de N cuerpos")
plt.axis("equal")
plt.grid()
plt.show()
