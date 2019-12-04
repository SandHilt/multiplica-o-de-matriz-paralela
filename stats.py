#! python3
from matplotlib import use, pyplot as plt
import numpy as np


def ler_arquivo(file):
    data = []

    for x in file.readlines():
        data.append(float(x))

    return data


boxdata = []

for estilo in ['serial', 'mpi', 'omp']:
    for projeto in ['matriz']:
        f = open('{:s}/{:s}/saida.dat'.format(
            estilo, projeto
        ), 'r')
        data = ler_arquivo(f)
        boxdata.append(data)

        print('media', round(np.mean(data), 5))
        print('desvio_padrao_amostral', round(np.std(data, ddof=1), 5))


plt.boxplot(boxdata, vert=False)
plt.grid(True)
plt.show()

f.close()

# speedup = tempo_sequencial / mean(tempos_paralelos)
# eficiencia = speedup / processadores * 100

# print('speedup', speedup)
# print('eficiencia', eficiencia)
