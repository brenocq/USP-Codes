import numpy as np
from matplotlib import pyplot as plt

# Default parameter values
m_ = (40*5*2)*1000.0 # Mass in kg/g
c_ = 4185.0 # Specific heat value of water (J/kg*C)
A_ = 40.0*5 # Basin surface area
h_ = 10.0 # Heat transfer ratio between water and air (W/m^2 K)
f_ = 5.0/3.0 # Flow rate of water out of basin

#---------- External temperature ----------#
def TextConst(t):
    return t/t*20.0

def TextHot(t):
    hour = t/3600.0
    return 35.0 + 5.0*np.sin((hour-8.0)/24.0*(2*np.pi))

def TextAvg(t):
    hour = t/3600.0
    return 9.7 + 4.7*np.sin((hour-8.0)/24.0*(2*np.pi))

#---------- ODE solvers ----------#
def analytical(step, N, m=m_, c=c_, A=A_, h=h_, f=f_):
    # Only supports TextConst
    T = np.zeros(N+1)
    Text = TextConst(0)
    T[0] = Text
    k = Text - (f*c*90+h*A*Text)/(f*c+h*A)

    for i in range(N):
        t = (i+1)*step
        T[i+1] = k*np.exp(-(f*c+h*A)/(m*c)*t) + (f*c*90+h*A*Text)/(f*c+h*A)
    return T

def eulerMethod(step, N, m=m_, c=c_, A=A_, h=h_, f=f_, Text=TextConst):
    T = np.zeros(N+1)
    T[0] = Text(0)

    for i in range(N):
        t = (i+1)*step
        Qgain = f*c*(90-T[i])
        Qloss = h*A*(T[i]-Text(t))
        T[i+1] = T[i]+step*(Qgain-Qloss)/(m*c)
    return T

def rk4Method(step, N, m=m_, c=c_, A=A_, h=h_, f=f_, Text=TextConst):
    T = np.zeros(N+1)
    T[0] = Text(0)

    def I(y, t):
        Qgain = f*c*(90-y)
        Qloss = h*A*(y-Text(t))
        return (Qgain-Qloss)/(m*c)

    k = np.zeros(4)
    for i in range(N):
        t = (i+1)*step
        k[0] = step*I(T[i], t)
        k[1] = step*I(T[i]+k[0]/2, t)
        k[2] = step*I(T[i]+k[1]/2, t)
        k[3] = step*I(T[i]+k[1], t)
        T[i+1] = T[i] + 1/6*(k[0]+2*k[1]+2*k[2]+k[3])
    return T

##############################
# External Temperature
#x = np.linspace(0, 2*24*3600, 10000, endpoint=True)
#fig = plt.figure()
#plt.plot(x/3600, TextConst(x), "k", label="Constant=20")
#plt.plot(x/3600, TextHot(x), "r", label="Hot Netherlands")
#plt.plot(x/3600, TextAvg(x), "b", label="Average Netherlands")
#plt.legend(loc="lower right")
#plt.xlabel("Time (hour)")
#plt.ylabel("Text (°C)")
#plt.title("External temperatures", fontsize = 14)
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)

##############################
# Methods with extended model
#numDays = 20.0
#s = 3600.0
#N = int(numDays*24*3600/s)
#x = np.linspace(0, N*s, N+1, endpoint=True)/(24*3600)
#TeulerH = eulerMethod(step=s, N=N, Text=TextHot)
#TeulerA = eulerMethod(step=s, N=N, Text=TextAvg)
#Trk4H = rk4Method(step=s, N=N, Text=TextHot)
#Trk4A = rk4Method(step=s, N=N, Text=TextAvg)
#fig = plt.figure()
#plt.plot(x, TeulerH, "r", label="Hot temp (euler)")
#plt.plot(x, TeulerA, "--r", label="Avg temp (euler)")
#plt.plot(x, Trk4H, "b", label="Hot temp (rk4)")
#plt.plot(x, Trk4A, "--b", label="Avg temp (rk4)")
#plt.legend(loc="lower right")
#plt.xlabel("Time (days)")
#plt.ylabel("Basin temperature (°C)")
#plt.title("Methods with extended model", fontsize = 14)
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)

##############################
# Methods with extended model
#numDays = 20.0
#s = 3600.0
#N = int(numDays*24*3600/s)
#x = np.linspace(0, N*s, N+1, endpoint=True)/(24*3600)
#Trk4avg100 = rk4Method(step=s, N=N, h=100, Text=TextAvg)
#Trk4avg10 = rk4Method(step=s, N=N, h=10, Text=TextAvg)
#Trk4hot100 = rk4Method(step=s, N=N, h=100, Text=TextHot)
#Trk4hot10 = rk4Method(step=s, N=N, h=10, Text=TextHot)
#fig = plt.figure()
#plt.plot(x, Trk4avg100, "g", label="Avg temp, h=100")
#plt.plot(x, Trk4hot100, "b", label="Hot temp, h=100")
#plt.plot(x, Trk4avg10, "y", label="Avg temp, h=10")
#plt.plot(x, Trk4hot10, "r", label="Hot temp, h=10")
#plt.legend(loc="lower right")
#plt.xlabel("Time (days)")
#plt.ylabel("Basin temperature (°C)")
#plt.title("Best and worst cases", fontsize = 14)
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)

##############################
# How efficient
#numDays = 20.0
#s = 3600.0
#N = int(numDays*24*3600/s)
#x = np.linspace(0, N*s, N+1, endpoint=True)/(24*3600)
#best = rk4Method(step=s, N=N, h=100, Text=TextAvg)
#worst = rk4Method(step=s, N=N, h=10, Text=TextHot)
#fig = plt.figure()
#plt.plot(x, best, "g", label="Best case")
#plt.plot(x, worst, "r", label="Worst case")
#plt.legend(loc="lower right")
#plt.xlabel("Time (days)")
#plt.ylabel("Basin temperature (°C)")
#plt.title("Current situation", fontsize = 14)
#print(f'best: {best[-1]}C')
#print(f'worst: {worst[-1]}C')
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)

##############################
# Storage doubled
#numDays = 20.0
#s = 3600.0
#N = int(numDays*24*3600/s)
#x = np.linspace(0, N*s, N+1, endpoint=True)/(24*3600)
#bestOld = rk4Method(step=s, N=N, h=100, Text=TextAvg)
#worstOld = rk4Method(step=s, N=N, h=10, Text=TextHot)
#best = rk4Method(step=s, N=N, h=100, Text=TextAvg, f=f_*2)
#worst = rk4Method(step=s, N=N, h=10, Text=TextHot, f=f_*2)
#fig = plt.figure()
#plt.plot(x, bestOld, "--g", label="Best case (current)")
#plt.plot(x, best, "g", label="Best case (doubled data)")
#plt.plot(x, worstOld, "--r", label="Worst case (current)")
#plt.plot(x, worst, "r", label="Worst case (doubled data)")
#plt.legend(loc="lower right")
#plt.xlabel("Time (days)")
#plt.ylabel("Basin temperature (°C)")
#plt.title("Data storage doubled", fontsize = 14)
#print(f'best: {best[-1]}C')
#print(f'worst: {worst[-1]}C')
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)

##############################
# Storage and basin doubled
#numDays = 20.0
#s = 3600.0
#N = int(numDays*24*3600/s)
#x = np.linspace(0, N*s, N+1, endpoint=True)/(24*3600)
#bestOld = rk4Method(step=s, N=N, h=100, Text=TextAvg, f=f_*2)
#worstOld = rk4Method(step=s, N=N, h=10, Text=TextHot, f=f_*2)
#best = rk4Method(step=s, N=N, h=100, Text=TextAvg, f=f_*2, A=A_*2, m=m_*2)
#worst = rk4Method(step=s, N=N, h=10, Text=TextHot, f=f_*2, A=A_*2, m=m_*2)
#fig = plt.figure()
#plt.plot(x, bestOld, "--g", label="Best case (doubled data)")
#plt.plot(x, best, "g", label="Best case (doubled data and basin)")
#plt.plot(x, worstOld, "--r", label="Worst case (doubled data)")
#plt.plot(x, worst, "r", label="Worst case (doubled data and basin)")
#plt.legend(loc="lower right")
#plt.xlabel("Time (days)")
#plt.ylabel("Basin temperature (°C)")
#plt.title("Data storage and basin doubled", fontsize = 14)
#print(f'best: {best[-1]}C')
#print(f'worst: {worst[-1]}C')
#plt.draw()
#plt.waitforbuttonpress(0)
#plt.close(fig)
