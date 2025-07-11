# scripts/plot_results.py
import matplotlib.pyplot as plt
import numpy as np
import os # Import the os module

# --- DEBUG: Print current working directory ---
print(f"Current working directory (Python): {os.getcwd()}")
# ---------------------------------------------

# Cargar datos de la funcion de particion
data_Z = np.loadtxt("../results/funcion_particion.dat")
kBT_values_Z = data_Z[:, 0]
Z_exact_values = data_Z[:, 1]
Z_mc_values = data_Z[:, 2]

# Cargar datos de la energia media
data_E = np.loadtxt("../results/energia_media.dat")
kBT_values_E = data_E[:, 0]
E_exact_values = data_E[:, 1]
E_mc_values = data_E[:, 2]

# Graficar Funcion de Particion
plt.figure(figsize=(10, 6))
plt.plot(kBT_values_Z, Z_exact_values, label='Z Exacto', color='blue')
plt.plot(kBT_values_Z, Z_mc_values, 'o', label='Z Monte Carlo', color='red', markersize=4, alpha=0.6)
plt.xlabel('$k_B T / \\epsilon$')
plt.ylabel('$Z$')
plt.title('Función de Partición para un Sistema de Dos Niveles')
plt.legend()
plt.grid(True)
plt.savefig('../results/funcion_particion.png')
plt.show()

# Graficar Energia Media
plt.figure(figsize=(10, 6))
plt.plot(kBT_values_E, E_exact_values, label='$\\langle E \\rangle$ Exacta', color='blue')
plt.plot(kBT_values_E, E_mc_values, 'o', label='$\\langle E \\rangle$ Monte Carlo', color='red', markersize=4, alpha=0.6)
plt.xlabel('$k_B T / \\epsilon$')
plt.ylabel('$\\langle E \\rangle / \\epsilon$')
plt.title('Energía Media para un Sistema de Dos Niveles')
plt.legend()
plt.grid(True)
plt.savefig('../results/energia_media.png')
plt.show()