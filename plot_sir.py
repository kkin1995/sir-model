import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("sir_data.dat", delimiter = '\t')
time = data[:, 0]
S = data[:, 1]
I = data[:, 2]
R = data[:, 3]

total = S + I + R

plt.plot(time, S, label = "Susceptible")
plt.plot(time, I, label = "Infected")
plt.plot(time, R, label = "Recovered")
plt.plot(time, total, label = "Total")

plt.legend()

plt.show()