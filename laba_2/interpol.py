import matplotlib.pyplot as plt
import numpy as np  
import math

f = open("rez2.txt", 'r')
fch = open("chebpoints.txt", 'r')
datach = fch.readlines()
datach = list(map(float, datach[0][:-2].split()))
    
data = f.readlines()
amount = list(map(int, data[0].split()))
length = list(map(float, data[1].split()))
    
for i in range(len(length)):
    length[i] = np.log(length[i]) / np.log(2) 
    
data = data[2:]

def mnk(arr1 = [], arr2 = []):
    arr1_mean = sum(arr1)/len(arr1)
    arr2_mean = sum(arr1)/len(arr1)
    sum1 = 0
    sum2 = 0
    for i in range(len(arr1)):
        sum1 += (arr1[i] - arr1_mean)*(arr2[i] - arr2_mean)
        sum2 += (arr1[i] - arr1_mean)*(arr1[i] - arr1_mean)
    return sum1/sum2
    
data = [list(map(float, i[:-2].split())) for i in data]
for i in range(len(data)):
    data[i] = np.log(data[i]) / np.log(2)
fig, ax = plt.subplots()
for i in range(len(amount)):
    plt.plot(length, data[i], label = f'# of points: {amount[i]}')
    print(mnk(length, data[i]))

    
plt.plot(length, datach, label = 'cheb', color='red')
plt.grid('on')
plt.ylabel('Ошибка')
plt.xlabel('Длина отрезка')
    
ax.legend()
plt.show()
