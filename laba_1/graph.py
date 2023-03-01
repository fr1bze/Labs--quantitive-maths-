from operator import truediv
import math as m
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

x = []
y = []

x_log = []
y_log = []

flie = "/Users/mikhail/Desktop/test.txt"
f = open(flie, 'r+')
lines = f.readlines()
for line in lines:
    z = line.split() 
    x.append(float(z[0])) 
    y.append(float(z[1]))
f.close
min_y = min(y)

plt.semilogy(x, y, '-')
plt.semilogx(x, y, '-')
plt.annotate('h = '+ str(round(x[np.argmin(y)], 3)), xy = (x[np.argmin(y)],min_y),  xycoords='data', xytext=(x[np.argmin(y)], min_y * 1.5), textcoords='data', arrowprops=dict(facecolor='r'))
plt.axhline(min_y,color = 'red')
plt.xlabel('шаг', fontsize=16)
plt.ylabel('погрешность', fontsize=16)
plt.grid(which='major')
plt.show()
