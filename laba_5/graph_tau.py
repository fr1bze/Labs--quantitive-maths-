from operator import truediv
import numpy as np
import math as m
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

i = []
res = []

flie = "/Users/mikhail/Desktop/tau.txt"
f = open(flie, 'r+')
lines = f.readlines()
for line in lines:
    z = line.split(':') 
    i.append(float(z[0])) 
    res.append(float(z[1]))
f.close

i_new_1 = []
res_new_1 = []



for k in range(0,len(i)):
    i_new_1.append(i[k])
    res_new_1.append(res[k])
    



# print("----------------------")
# print(res_new_1)
# print("----------------------")
# print(res_new_2)


plt.plot(i_new_1,res_new_1)
plt.xlabel('tau', fontsize=12)
plt.ylabel('step', fontsize=16)
#plt.plot(i_new_3, res_new_3, '-')
 #plt.semilogx(x, y, '-')
# plt.annotate('h = '+ str(round(x[np.argmin(y)], 3)), xy = (x[np.argmin(y)],min_y),  xycoords='data', xytext=(x[np.argmin(y)], min_y * 1.5), textcoords='data', arrowprops=dict(facecolor='r'))
plt.grid(which='major')

plt.show()
