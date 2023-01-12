import pandas as pd
import matplotlib.pyplot as plt

"""performace Vs. block size"""
thread_names = []
df2=pd.read_excel('Part4-graph.xlsx')
x_vals=df2['Block size']
x_vals
thread_names = ["Without Cache", "With Cache"]
default_x_ticks = range(len(x_vals))


y_vals1=df2['Performance - without cache']
y_vals2=df2['Performance - with cache']
plt.rcParams["figure.figsize"] = [14.00, 10.50]
plt.rcParams.update({'font.size': 20})
plt.plot(default_x_ticks,y_vals1)
plt.plot(default_x_ticks,y_vals2)
plt.xticks(default_x_ticks,x_vals)
plt.xlabel('Block Size --->')
plt.ylabel('Performance(in MiB/sec) --->')
plt.title('PART:4 - Performance Vs. Block Size (caching)')
plt.legend(thread_names)
plt.savefig("Part4 - performance x block size.png")
plt.show()