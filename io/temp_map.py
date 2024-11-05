import matplotlib.pyplot as plt
import seaborn as sns

data = [
    [0, 2.4, 6.8, 17.4, 26, 47, 60.2],
    [0, 4, 9.4, 21, 42, 64.2, 93.2],
    [0, 4.2, 12, 31.6, 52.8, 68.8, 130.4],
    [1, 5.4, 14.6, 30.8, 47, 97, 132],
    [0, 5, 17, 29.2, 51.8, 102, 141.2],
    [1, 6, 18.2, 33, 57, 103.4, 142.8],
    [1, 5.2, 17.2, 36.2, 66.2, 116, 170],
    [1, 6.6, 18, 40.8, 80.6, 148.2, 214.6],
    [1.2, 6.2, 20.8, 41.4, 78, 122.8, 208]
]
data.reverse()
h = sns.heatmap(data, xticklabels=[100 + 100 * x for x in range(7)],
                yticklabels=[10 - x for x in range(9)],
                cmap=sns.cm.rocket_r)
plt.xlabel('Tasks number')
plt.ylabel('Processors number')
plt.show()
