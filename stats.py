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
size = " "

if len(argv) == 2:
    size = argv[1]

serial = 0
speedup = []
eficiencia = []

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
            sp = serial / np.mean(data)
            proc = int(estilo[-1])

            speedup.append(sp)
            eficiencia.append(sp / proc * 100)


        print('Para o {:s}:'.format(str(estilo)))
        print('media', round(np.mean(data), 5))
        print('desvio_padrao_amostral', round(np.std(data, ddof=1), 5))
        print("-"*20)


plt.subplot(1,2,1)

plt.boxplot(boxdata, labels=estilos, vert=False)
plt.grid(True)
plt.xlabel("Tempo (s)")
plt.title("Tempos de execucao {:s}".format(size))


plt.subplot(2,2,2)
plt.title("Speedup")
plt.barh(parallel, speedup)


plt.subplot(2,2,4)
plt.title("Eficiência")
plt.bar(parallel, eficiencia)

plt.savefig('./boxplot.png')
plt.show()

# speedup = tempo_sequencial / mean(tempos_paralelos)
# eficiencia = speedup / processadores * 100