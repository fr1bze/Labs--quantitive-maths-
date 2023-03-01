from operator import truediv
import numpy as np
import math as m
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

i = []
res = []

flie = "/Users/mikhail/Desktop/firstFunc.txt"
f = open(flie, 'r+')
lines = f.readlines()
for line in lines:
    z = line.split(':') 
    i.append(float(z[0])) 
    res.append(float(z[1]))
f.close

i_new_1 = []
res_new_1 = []

i_new_2 = []
res_new_2 = []

for k in range(0,len(i),2):
    i_new_1.append(i[k])
    res_new_1.append(res[k])
    i_new_2.append(i[k+1])
    res_new_2.append(res[k+1])



# print("----------------------")
# print(res_new_1)
# print("----------------------")
# print(res_new_2)


fig, axes = plt.subplots(2,1, figsize=(12, 8), sharex=True)
axes[0].semilogy(i_new_1,np.abs(res_new_1))
axes[1].semilogy(i_new_2,np.abs(res_new_2))
axes[0].set_xlabel('шаг', fontsize=12)
axes[1].set_xlabel('шаг', fontsize=12)
axes[0].set_ylabel('погрешность', fontsize=16)
axes[1].set_ylabel('погрешность', fontsize=16)
#plt.plot(i_new_3, res_new_3, '-')
 #plt.semilogx(x, y, '-')
# plt.annotate('h = '+ str(round(x[np.argmin(y)], 3)), xy = (x[np.argmin(y)],min_y),  xycoords='data', xytext=(x[np.argmin(y)], min_y * 1.5), textcoords='data', arrowprops=dict(facecolor='r'))
axes[0].grid(which='major')
axes[1].grid(which='major')
axes[0].set_title('Метод половинного деления')
axes[1].set_title('Метод Ньютона')
plt.show()
