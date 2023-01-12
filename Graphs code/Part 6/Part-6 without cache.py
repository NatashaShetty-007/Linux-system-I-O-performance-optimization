import pandas as pd
import matplotlib.pyplot as plt

"""without catch"""

df=pd.read_excel('withoutcatch.xlsx')

x_vals=df['Unnamed: 0']
x_vals
default_x_ticks = range(len(x_vals))


threads_1=df['1 thread']
threads_2=df['2 threads']
threads_4=df['4 threads']
threads_8=df['8 threads']
threads_16=df['16 threads']
threads_32=df['32 threads']

plt.rcParams["figure.figsize"] = [14.00, 10.50]
plt.rcParams.update({'font.size': 20})
plt.plot(default_x_ticks,threads_1,label = "1 threads")
plt.plot(default_x_ticks,threads_2,label = "2 threads")
plt.plot(default_x_ticks,threads_4,label = "4 threads")
plt.plot(default_x_ticks,threads_8,label = "8 threads")
plt.plot(default_x_ticks,threads_16,label = "16 threads")
plt.plot(default_x_ticks,threads_32,label = "32 threads")
plt.xticks(default_x_ticks,x_vals)
plt.xlabel('Block Size --->')
plt.ylabel('Performance( in MiB/sec ) -->')
plt.title('PART:6 - Performance x BlockSize without cache graph')
plt.legend()

plt.savefig("Part6 - without cache.png.png")
plt.show()
