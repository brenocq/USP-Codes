'''
Short Assignment 2: Image Restoration

Breno Cunha Queiroz - 11218991
Course SCC0251 - USP
05/07/2020 - semestre 3
'''

import numpy as np
import imageio
from scipy.fftpack import fftn, ifftn, fftshift

def gaussian_filter(k, sigma):
   arx = np.arange((-k // 2) + 1.0, (k // 2) + 1.0)
   x, y = np.meshgrid(arx, arx)
   filt = np.exp( -(1/2)*(np.square(x) + np.square(y))/np.square(sigma) )
   return filt/np.sum(filt)

def image_normalization(filtered, maxVal):
    maxFiltered = np.max(filtered)
    minFiltered = np.min(filtered)
    normalized = np.zeros(filtered.shape, dtype=np.int32)

    return np.divide(np.multiply(np.subtract(filtered.astype(np.float), minFiltered), maxVal), np.subtract(maxFiltered, minFiltered))

def least_square(G, H, P, gamma):
    F_hat = (H.conjugate() / (np.abs(H)**2 + gamma*np.abs(P)**2)) * G
    return F_hat

def evaluate(f):
    stdDev = np.round(np.std(f[:]),1)
    print("{0:.1f}".format(stdDev,1))

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
g = gaussian_filter(k, sigma)

# Add padding to gaussian filter
a = int(f.shape[0]//2 - g.shape[0]//2)
g_pad = np.pad(g, (a,a-1), 'constant', constant_values=(0))

# Transform to fourier domain
F = fftn(f)
G = fftn(g_pad)

# Convolution
H = np.real(fftshift(ifftn(np.multiply(G,F))))

# Normalize after denoising
H_norm_ = image_normalization(H, np.max(f))
H_norm = fftn(H_norm_)

# Laplacian operator
p = np.array([[0,-1,0],[-1,4,-1],[0,-1,0]])
a = int(f.shape[0]//2 - 3//2)
p_pad = np.pad(p, (a,a-1), 'constant', constant_values=(0))
P = fftn(p_pad)

# Constrained Least Squares method (Laplacian regularization)
F_hat = least_square(H_norm, G, P, gamma)

# Normalize after blur removal
f_hat = ifftn(F_hat).real
f_new = image_normalization(f_hat, np.max(H_norm_))

# Evaluated transformed image
evaluate(f_new)
