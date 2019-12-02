#! python3
from statistics import mean
from matplotlib import use, pyplot as plt
import numpy as np

f = open('omp/matriz/saida.dat', 'r')

data = []

# Mostando o que tem no arquivo
for x in f.readlines():
    y = float(x)
    data.append(y)

plt.boxplot(data, vert=False)
plt.grid(True)
plt.show()

f.close()

# speedup = tempo_sequencial / mean(tempos_paralelos)
# eficiencia = speedup / processadores * 100

# print('speedup', speedup)
# print('eficiencia', eficiencia)
