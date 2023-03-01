from tokenize import Double
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import numpy as np

steps = [0]*1000
s2 = []
s4 = []
s8 = []
s16 = []
s32 = []
s64 = []
s128 = []

flie = "/Users/mikhail/Desktop/labs/laba_3/data3.txt"
def reader(file, line_num):
    f = open(file, 'r+')
    lines = f.readlines()
    z = []
    mas = []
    z = lines[line_num].split()
    for j in range(len(z)):
        mas.append(z[j])
    return mas


s2 = reader(file="/Users/mikhail/Desktop/labs/laba_3/data3.txt",line_num=0)
print(len(s2))

def mnk(arr1 = [], arr2 = []):
    arr1_mean = sum(arr1)/len(arr1)
    arr2_mean = sum(arr1)/len(arr1)
    sum1 = 0
    sum2 = 0
    for i in range(len(arr1)):
        sum1 += (arr1[i] - arr1_mean)*(arr2[i] - arr2_mean)
        sum2 += (arr1[i] - arr1_mean)*(arr1[i] - arr1_mean)
    return sum1/sum2

delta = []

for i in range(1000):
    steps[i]= 3/999 * i
print(len(steps))
print(steps)
print(s2)
fig, axs = plt.subplots(3, 3)

plt.plot(steps,s2)
plt.show()
   