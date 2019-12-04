#! python3
from matplotlib import use, pyplot as plt
from itertools import product

import numpy as np


def ler_arquivo(file):
    data = []

    for x in file.readlines():
        data.append(float(x))

    return data


boxdata = []
parallel = list(product(['omp', 'mpi'], [2, 4]))

for projeto in ['matriz']:
    for estilo in ['serial'] + parallel:
        if estilo == 'serial':
            filename = '{:s}_{:s}.dat'.format(projeto, estilo)
        else:
            filename = '{:s}_{:s}_{:d}.dat'.format(
                projeto, estilo[0], estilo[1])

        f = open(filename, 'r')
        data = ler_arquivo(f)
        boxdata.append(data)

        print('media', round(np.mean(data), 5))
        print('desvio_padrao_amostral', round(np.std(data, ddof=1), 5))


plt.boxplot(boxdata, labels=['serial'] + parallel, vert=False)
plt.grid(True)
plt.savefig('./boxplot.png')
plt.show()

f.close()

# speedup = tempo_sequencial / mean(tempos_paralelos)
# eficiencia = speedup / processadores * 100

# print('speedup', speedup)
# print('eficiencia', eficiencia)
