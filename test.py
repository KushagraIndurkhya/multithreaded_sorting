import matplotlib.pyplot as plt
import numpy as np

y1=[5557,8775,11857,10797,13468]
y2=[5070,6205,5931,12773,17391]
y3=[]
x= [2,3,4,5,6]

plt.plot(x, y1, label="Solution-1")
plt.plot(x, y2, label="Solution-2")
# plt.plot(x1, y, label="Simple")

plt.xlabel('P where no of threads=2^p') 
plt.ylabel('Time in microseconds')
plt.xticks(np.arange(min(x), max(x)+1, 1.0))
plt.title("Graph-1")
plt.grid(True)
plt.legend()
plt.show()
