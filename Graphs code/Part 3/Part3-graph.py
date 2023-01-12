import pandas as pd
import matplotlib.pyplot as plt

"""performace Vs. block size"""

df2=pd.read_excel('Part3-graph.xlsx')


x_vals=df2['Block Size']
x_vals
default_x_ticks = range(len(x_vals))


y_vals=df2['Performance']
plt.rcParams["figure.figsize"] = [14.00, 10.50]
plt.rcParams.update({'font.size': 20})
plt.plot(default_x_ticks,y_vals)
plt.xticks(default_x_ticks,x_vals)
plt.xlabel('Block Size --->')
plt.ylabel('Performance(in MiB/sec) --->')
plt.title('PART:3 - Performance Vs. Block Size')
plt.savefig("Part3 - performance x block size.png")
plt.show()

