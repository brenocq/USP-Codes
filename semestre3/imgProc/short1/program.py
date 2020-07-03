'''
Short Assignment 1: Filtering in Fourier Domain

Breno Cunha Queiroz - 11218991
Course SCC0251 - USP
02/07/2020 - semestre 3
'''
import numpy as np
import imageio
import matplotlib.pyplot as plt
import time

# implementing a 2D version of the DFT
def DFT2D(f):
    # create empty array of complex coefficients
    F = np.zeros(f.shape, dtype=np.complex64)
    n,m = f.shape[0:2]
    start = time.time()

    # creating indices for x, to compute multiplication using numpy (f*exp)
    x = np.arange(n)
    # for each frequency 'u,v'
    for u in np.arange(n):
        for v in np.arange(m):
            for y in np.arange(m):
                F[u,v] += np.sum(f[:,y] * np.exp( (-1j*2*np.pi) * (((u*x)/n)+((v*y)/m)) ))


    end = time.time()
    elapsed = end - start

    print("Image size: " + str(n*m))
    print("Running time: %.5f sec." %  elapsed)

    return F/np.sqrt(n*m)

def setPixelsToZero(F, thresh):
    w,h = F.shape[0:2]

    # 2nd maximum value
    p2 = 0

    # Find pixel with second highest value
    for y in np.arange(h):
        for x in np.arange(w):
            if x==0 and y==0:
                continue
            if np.abs(F[y][x]) > p2:
                p2 = F[y][x]

    # Reset pixels to zero using threshold
    for y in np.arange(h):
        for x in np.arange(w):
            if np.abs(F[y][x]) < p2*thresh:
                F[y][x] = 0
    return F


###############################################################
########################### MAIN CODE #########################
###############################################################

# Input file name
file = 'moon_small.png'
# Read image
img = imageio.imread(file)
# Image to perform transformations
transformed = img

# Compute discrete fourier transform
Fimg = DFT2D(transformed)

plt.figure(figsize=(8,8))
plt.subplot(131)
plt.imshow(transformed, cmap="gray")
plt.axis('off')
# the power spectrum
plt.subplot(132)
plt.imshow(np.abs(Fimg)**2, cmap="gray")
plt.axis('off')
test = setPixelsToZero(Fimg, 1)
plt.subplot(133)
plt.imshow(np.abs(test)**2, cmap="gray")
plt.axis('off')

plt.show()
