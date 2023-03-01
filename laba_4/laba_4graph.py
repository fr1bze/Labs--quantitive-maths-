from tokenize import Double
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

steps = []
x1 = []
x2 = []
x3 = []
x4 = []

def mnk(arr1 = [], arr2 = []):
    arr1_mean = sum(arr1)/len(arr1)
    arr2_mean = sum(arr1)/len(arr1)
    sum1 = 0
    sum2 = 0
    for i in range(len(arr1)):
        sum1 += (arr1[i] - arr1_mean)*(arr2[i] - arr2_mean)
        sum2 += (arr1[i] - arr1_mean)*(arr1[i] - arr1_mean)
    return sum1/sum2

flie = "/Users/mikhail/Desktop/labs/laba_4/data.txt"
f = open(flie, 'r+')
lines = f.readlines()
for line in lines:
    z = line.split()
    steps.append(np.double(z[0]))
    x1.append(np.double(z[1])) 
    x2.append(np.double(z[2]))
    x3.append(np.double(z[3])) 
    x4.append(np.double(z[4]))

for i in range(len(x1)):
    steps[i] = np.log(steps[i])
    x1[i] = np.log(x1[i])/np.log(10)
    x2[i] = np.log(x2[i])/np.log(10)
    x3[i] = np.log(x3[i])/np.log(10)
    x4[i] = np.log(x4[i])/np.log(10)
print("n = 2 ", mnk(steps[:10], x1[:10]))
print("n = 3 ", mnk(steps[:10], x2[:10]))
print("n = 4 ", mnk(steps[:10], x3[:10]))
print("n = 5 ", mnk(steps[:5], x4[:5]))

fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(steps, x1,'.', color = 'red')
axs[0, 0].set_title('Для n = 2')
axs[0, 1].plot(steps, x2, '.',color = 'blue')
axs[0, 1].set_title('Для n = 3')
axs[1, 0].plot(steps, x3, '.',color = 'orange')
axs[1, 0].set_title('Для n = 4')
axs[1, 1].plot(steps,x4, '.',color = 'green')
axs[1, 1].set_title('Для n = 5')
for i in range(2):
    for j in range(2):
        axs[i,j].set_xlabel("Шаг")
        axs[i,j].set_ylabel("Ошибка")
plt.show()