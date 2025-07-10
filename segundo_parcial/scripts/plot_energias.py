import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("results/energiasN.dat")
t = data[:, 0]
Ek = data[:, 1]
Ep = data[:, 2]
Et = data[:, 3]

plt.plot(t, Ek, label="Cinética")
plt.plot(t, Ep, label="Potencial")
plt.plot(t, Et, label="Total", linestyle='--')
plt.xlabel("Tiempo")
plt.ylabel("Energía")
plt.title("Energías del sistema")
plt.legend()
plt.grid()
plt.show()
