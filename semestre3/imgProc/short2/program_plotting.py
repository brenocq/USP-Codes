'''
Short Assignment 2: Image Restoration

Breno Cunha Queiroz - 11218991
Course SCC0251 - USP
05/07/2020 - semestre 3
'''
import numpy as np
import imageio
import matplotlib.pyplot as plt
from scipy.fftpack import fftn, ifftn, fftshift

def gaussian_filter(k=3, sigma=1.0):
   arx = np.arange((-k // 2) + 1.0, (k // 2) + 1.0)
   x, y = np.meshgrid(arx, arx)
   filt = np.exp( -(1/2)*(np.square(x) + np.square(y))/np.square(sigma) )
   return filt/np.sum(filt)

def image_normalization(filtered, maxVal):
    maxFiltered = np.max(filtered)
    minFiltered = np.min(filtered)
    normalized = np.zeros(filtered.shape, dtype=np.int32)

    n,m = filtered.shape[0:2]

    for y in np.arange(m):
        for x in np.arange(n):
            normalized[y][x] = float(filtered[y][x]-minFiltered)/(maxFiltered-minFiltered)*maxVal

    return normalized

###############################################################
########################### MAIN CODE #########################
###############################################################

file = str(input()).rstrip()
k = int(input())
sigma = float(input())
gamma = float(input())

# Read image
f = imageio.imread(file)

# Gaussian filter 
h = gaussian_filter(k, sigma)

# Add padding to gaussian filter
a = int(f.shape[0]//2 - h.shape[0]//2)
h_pad = np.pad(h, (a,a-1), 'constant', constant_values=(0))

# Transform to fourier domain
F = fftn(f)
H = fftn(h_pad)

# FFT shift
#F = np.fft.fftshift(F)
#H = np.fft.fftshift(h_pad)

# Convolution
G = np.multiply(F,H)
g = fftshift(ifftn(G).real)

plt.figure(figsize=(8,4))
plt.subplot(251)
plt.imshow(f, cmap="gray")
plt.axis('off')

plt.subplot(252)
plt.imshow(np.fft.fftshift(np.log(1+np.abs(F))), cmap="gray")
plt.axis('off')

plt.subplot(253)
plt.imshow(np.fft.fftshift(np.log(1+np.abs(H))), cmap="gray")
plt.axis('off')

plt.subplot(254)
plt.imshow(np.fft.fftshift(np.log(1+np.abs(G))), cmap="gray")
plt.axis('off')

plt.subplot(255)
plt.imshow(g, cmap="gray")
plt.axis('off')

# Normalize after denoising
normalized = image_normalization(g, np.max(f))

plt.subplot(256)
plt.imshow(normalized, cmap="gray")
plt.axis('off')

# Constrained Least Squares method (Laplacian regularization)

plt.show()
