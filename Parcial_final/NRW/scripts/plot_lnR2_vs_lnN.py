import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv('../results/data.csv')
x = data['lnN']
y = data['ln<R2>']

# Ajuste lineal
coef = np.polyfit(x, y, 1)
a, b = coef
print(f"Ajuste: y = {a:.4f} ln(N) + {b:.4f}")

plt.plot(x, y, 'o', label='Datos')
plt.plot(x, a*x + b, '-', label=f'Ajuste: y = {a:.4f} ln(N) + {b:.4f}')
plt.xlabel('ln(N)')
plt.ylabel('ln(<R²>)')
plt.legend()
plt.grid()
plt.savefig('../results/grafica_lnR2_vs_lnN.png')
plt.show()
