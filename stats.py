#! python3
from matplotlib import use, pyplot as plt
from sys import argv

import numpy as np


def ler_arquivo(file):
    data = []

    for x in file.readlines():
        data.append(float(x))

    return data


boxdata = []
parallel = ["_".join([x, y]) for x in ['mpi', 'omp'] for y in ['2', '4']]
estilos = ['serial'] + parallel

serial = 0
speedup = []

for projeto in ['matriz']:
    for estilo in estilos:
        filename = '{:s}_{:s}.dat'.format(projeto, estilo)

        f = open(filename, 'r')
        data = ler_arquivo(f)
        f.close()
        boxdata.append(data)

        if estilo == 'serial':
            serial = np.mean(data)
        else:
            speedup.append(serial / np.mean(data))

        print('Para o {:s}:'.format(str(estilo)))
        print('media', round(np.mean(data), 5))
        print('desvio_padrao_amostral', round(np.std(data, ddof=1), 5))
        print("-"*20)


plt.boxplot(boxdata, labels=estilos, vert=False)
plt.grid(True)
plt.xlabel("Tempo (s)")
plt.title("Tamanho {:s}".format(argv[1]))
plt.savefig('./boxplot.png')
plt.show()

# plt.figure()
# plt.barh(parallel, range(4))
# plt.show()

# speedup = tempo_sequencial / mean(tempos_paralelos)
# eficiencia = speedup / processadores * 100

# print('speedup', speedup)
# print('eficiencia', eficiencia)
