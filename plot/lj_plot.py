
import numpy as np 
import matplotlib.pyplot as plt

r = np.linspace(1,1.5,1001);

def lj_pot(r):
    return 4.*(r**-12 - r**-6)

def lj_force(r):
    return -4.*(12.*r**-13 - 6.*r**-7)

equil_r = 2.**(1./6.)

print equil_r

print(lj_force(equil_r))

print r[np.argmin(np.abs(lj_force(r)))]

dr = r[1] - r[0]

lj_pot_grad = np.gradient(lj_pot(r), dr)

fig = plt.figure()

ax = fig.add_subplot(211)
plt.plot(r, lj_pot(r), 'r')
plt.ylim([-1.,1.])

ax = fig.add_subplot(212)
plt.plot(r, lj_pot_grad, 'b')
plt.plot(r, lj_force(r), 'm--')
plt.ylim([-2.5,2.5])
plt.show()