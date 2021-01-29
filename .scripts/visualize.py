import matplotlib.pyplot as plt
import numpy as np

x1= [2,3,4,5,6]
x2= [13,14,15,16,17]
y1=[]
y2=[]
file_names=[]
for _ in range(6):
    file_names.append(input())
# print(file_names)
file_pntrs=[]
for fn in file_names[0:3]:
    temp=[]
    for line in open(fn, 'r'):
        temp.append(int(line))
    y1.append(temp)
for fn in file_names[3:6]:
    temp=[]
    for line in open(fn, 'r'):
        temp.append(int(line))
    y2.append(temp)
fig1=plt.figure(1)
plt.plot(x1, y1[0], label="Solution-1")
plt.plot(x1, y1[1], label="Solution-2")
plt.plot(x1, y1[2], label="Solution-3")

plt.xlabel('P where no of threads=2^p') 
plt.ylabel('Time in microseconds')
plt.xticks(np.arange(min(x1), max(x1)+1, 1.0))
plt.title("Graph-1")
plt.grid(True)
plt.legend()

fig1=plt.figure(2)
plt.plot(x2, y2[0], label="Solution-1")
plt.plot(x2, y2[1], label="Solution-2")
plt.plot(x2, y2[2], label="Solution-3")

plt.xlabel('n where no of elements=2^n') 
plt.ylabel('Time in microseconds')
plt.xticks(np.arange(min(x2), max(x2)+1, 1.0))
plt.title("Graph-2")
plt.grid(True)
plt.legend()
plt.show()
