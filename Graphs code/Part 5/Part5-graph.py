import pandas as pd
import matplotlib.pyplot as plt

"""performace Vs. filesize"""

df2=pd.read_excel('Part5-graph.xlsx')


x_vals=df2['File Size']
x_vals
x_val=[0,20,40,60,80,100,120]
default_x_ticks = range(len(x_vals))


y_vals=df2['Performance']
plt.rcParams["figure.figsize"] = [14.00, 10.50]
plt.rcParams.update({'font.size': 20})
plt.plot(default_x_ticks,y_vals)
plt.xticks(default_x_ticks,x_val)
plt.xlabel('File Size --> ')
plt.ylabel('Performance (in MiB/sec) --->')
plt.title('PART:5 - Performance Vs. File Size')


plt.savefig("Part5 - performance x File size.png")
plt.show()