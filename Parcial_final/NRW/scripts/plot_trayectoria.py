import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/trayectoria.csv")
plt.figure(figsize=(6, 6))
plt.plot(df['x'], df['y'], marker='o', markersize=1, linewidth=0.5)
plt.title("Caminata Aleatoria 2D")
plt.xlabel("x")
plt.ylabel("y")
plt.axis('equal')
plt.grid(True)
plt.savefig("results/trayectoria.png")
plt.show()
