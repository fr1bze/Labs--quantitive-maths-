from operator import truediv
import numpy as np
import math as m
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

x = []
y = []
flie1 = "/Users/mikhail/Desktop/x.txt"
f = open(flie1, 'r+')
lines = f.readlines()
for line in lines:
    z = line.split() 
    x.append(float(z[0]))
f.close

file2= "/Users/mikhail/Desktop/y.txt"
f2 = open(file2, 'r+')
lines = f2.readlines()
for line in lines:
    z = line.split() 
    y.append(float(z[0]))
f.close

plt.plot(x,y)
plt.xlabel('x', fontsize=12)
plt.ylabel('y', fontsize=16)
plt.grid(which='major')
plt.title('Зависимость ошибки от шага')
plt.show()
