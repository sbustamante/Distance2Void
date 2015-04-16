import numpy as np
import matplotlib.pylab as plt

datos = np.loadtxt( "C_HaloVoid_FOF-Tweb.dat" )

Nneigh = 5

for i in xrange(Nneigh):
    plt.hist( datos[:,i*5], range=(0,50), bins=500, normed=True, alpha=0.5 )
    print( "Percent of halos without %d-th neighbour = %1.2f"%(i+1,(datos[:,i*5]>150).sum()/(1.0*len(datos))*100))
plt.show()
