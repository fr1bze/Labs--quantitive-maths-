from tokenize import Double
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np
import math as m

def func(x):
    return np.cos(x)

def get_max(arr1 = [], arr2 = []):
    errors = []
    for i in range(len(arr2)):
        errors.append(abs(arr1[i] - arr2[i]))
    return max(errors)


def mnk(arr1 = [], arr2 = []):
    arr1_mean = sum(arr1)/len(arr1)
    arr2_mean = sum(arr2)/len(arr2)
    sum1 = 0
    sum2 = 0
    for i in range(len(arr1)):
        sum1 += (arr1[i] - arr1_mean)*(arr2[i] - arr2_mean)
        sum2 += (arr1[i] - arr1_mean)*(arr1[i] - arr1_mean)
    return sum1/sum2

steps = []
f1 = []
lines = []
delta = []
points =[]

for i in range (7):
    points.append(2**(i+1))
for i in range(1000):
    steps.append(3/999 * i)
for i in range(1000):
    f1.append(func(steps[i]))

flie = "data3.txt"
f = open(flie, 'r+')
fig, ax = plt.subplots()
for i in range(7):
    lines.append(np.double(f.readline().split()))
for i in range(7):
    delta.append(get_max(f1, lines[i]))

points_log = np.log(points)
delta_log = np.log(delta)
print(mnk(points_log,delta_log))
x = [1,2,3,4,5,6,7]
y = [0]*7
k = mnk(points_log,delta_log)
for i in range(len(x)):
    y[i]= x[i]*k + 0.75
plt.plot(points,delta)
#plt.semilogy(points, delta)
plt.xlabel("Кол-во точек")
plt.ylabel("Ошибка")
plt.show()