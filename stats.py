#! python3
from matplotlib import use, pyplot as plt
import numpy as np


def ler_arquivo(file):
    data = []

    for x in file.readlines():
        data.append(float(x))

    return data


boxdata = []

for prefixo in ['serial', 'serialsum', 'paralela1for', 'paralela2for']:
    for N in ['1000']:
        name = '_'.join([N, prefixo])
        f = open('omp/matriz/saida_{:s}.dat'.format(name), 'r')
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
