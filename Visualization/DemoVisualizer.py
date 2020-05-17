import matplotlib.pyplot as plt
import numpy as np
import time


data_inherent_risk = np.loadtxt('../Results/CalculatedRisksPerDomain.csv', delimiter=',', usecols = (1,), skiprows=1)
data_residual_risk = np.loadtxt('../Results/CalculatedRisksPerDomain.csv', delimiter=',', usecols = (2,), skiprows=1)

data_inherent_risk = data_inherent_risk.transpose()
data_residual_risk = data_residual_risk.transpose()

# import the tick labels

xt_risk = np.loadtxt('../Results/CalculatedRisksPerDomain.csv', dtype='str', delimiter=',', usecols = (0,), skiprows=1)

width = 0.45
ind = np.arange(xt_risk.shape[0]) + 0.75

fig, ax = plt.subplots(1,1)

p0 = ax.bar(ind, data_inherent_risk,  width, color = 'blue')
p1 = ax.bar(ind+width, data_residual_risk,  width, color = 'red')


ax.set_ylabel('Normalized Risk')
ax.set_xlabel('Risk Domain')

ax.set_xticks (ind + width/2.)
ax.set_xticklabels( xt_risk, rotation = 70 )


fig.legend( (p0[0],p1[0]), ('Inherent Risk','Residual Risk') )
fig.tight_layout()
plt.show()
