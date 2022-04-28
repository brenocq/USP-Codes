import math
import numpy as np
from matplotlib import pyplot as plt

s = 3600.0 # Step size
N = 24*21 # Number of steps

m = (40*5*2)*1000.0 # Mass in kg/g
c = 4185.0 # Specific heat value of water (J/kg*C)
A = 40.0*5 # Basin surface area
h = 5.0 # Heat transfer ratio between water and air (W/m^2 K)
# https://www.engineersedge.com/heat_transfer/convective_heat_transfer_coefficients__13378.htm
f = 5/3# Flow rate of water out of basin

Text = 20.0 # External temperature
T = np.zeros(N+1) # Basin temperature in each step
T[0] = Text # Initial basin temperature


fig = plt.figure()
#---------- Numerical solution ----------#
for i in range(N):
    Qgain = f*c*(90-T[i])
    Qloss = h*A*(T[i]-Text)

    T[i+1] = T[i]+s*(Qgain-Qloss)/(m*c)

plt.plot(np.linspace(0, N*s, N+1, endpoint=True)/(3600*24), T, "*k", label="Numerical")

#------------ Exact solution ------------#
T = np.zeros(N+1)
T[0] = Text
k = Text - (f*c*90+h*A*Text)/(f*c+h*A)
for i in range(N):
    t = (i+1)*s
    T[i+1] = k*math.exp(-(f*c+h*A)/(m*c)*t) + (f*c*90+h*A*Text)/(f*c+h*A)

plt.plot(np.linspace(0, N*s, N+1, endpoint=True)/(3600*24), T, "-b", label="Exact")

#----------------- Plot -----------------#
plt.legend(loc="lower right")
plt.xlabel("Time (days)")
plt.ylabel("Basin temperature (°C)")
plt.title("Basin temperature x time", fontsize = 14)

plt.draw()
plt.waitforbuttonpress(0)
plt.close(fig)
