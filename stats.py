#! python3
from statistics import mean
from random import uniform
from matplotlib import pyplot as plt

f = open('matriz/saida.dat', 'r')

# Mostando o que tem no arquivo
for x in f.readlines():
    print(x)

f.close()

reps = 3
tempo_max = 4
processadores = 2
tempos_paralelos = []

tempo_sequencial = uniform(tempo_max * .75, tempo_max)

for i in range(reps):
    tempo_paralelo = uniform(tempo_max / processadores, .75 * tempo_max)
    tempos_paralelos.append(tempo_paralelo)
    
speedup = tempo_sequencial / mean(tempos_paralelos)
eficiencia = speedup / processadores * 100

print('speedup', speedup)
print('eficiencia', eficiencia)
