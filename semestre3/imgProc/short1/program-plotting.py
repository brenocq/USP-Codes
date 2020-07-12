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

def DFT2D(f):
    '''
    2D version of the DFT
    '''
    # implementing a 2D version of the DFT
    # create empty array of complex coefficients
    F = np.zeros(f.shape, dtype=np.complex64)
    n,m = f.shape[0:2]

    # creating indices for x, to compute multiplication using numpy (f*exp)
    x = np.arange(n).reshape(n,1)
    y = np.arange(m).reshape(1,m)
    # for each frequency 'u,v'
    for u in np.arange(n):
        for v in np.arange(m):
            F[u,v] = np.sum(f * np.exp( (-1j*2*np.pi) * (((u*x)/n)+((v*y)/m)) ))


    return F/np.sqrt(n*m)

def IDFT2D(F):
    '''
    2D version of the IDFT
    '''
    # implementing a 2D version of the IDFT
    # create empty array of complex coefficients
    f = np.zeros(F.shape, dtype=np.complex64)
    n,m = F.shape[0:2]

    # creating indices for x, to compute multiplication using numpy (f*exp)
    u = np.arange(n).reshape(n,1)
    v = np.arange(m).reshape(1,m)
    # for each frequency 'u,v'
    for x in np.arange(n):
        for y in np.arange(m):
            f[x,y] = np.sum(F * np.exp( (1j*2*np.pi) * (((u*x)/n)+((v*y)/m)) ))

    return np.abs(np.real(f/np.sqrt(n*m)))

def setPixelsToZero(F, thresh):
    '''
    Set as zero all pixels below threshold from the second highest pixel
    '''
    w,h = F.shape[0:2]
    Fzero = F

    # Number of filtered pixels
    qtyFiltered = 0
    # maximum value
    p1 = 0
    # 2nd maximum value
    p2 = 0

    # Find pixel with second highest value
    for y in np.arange(h):
        for x in np.arange(w):
            if np.abs(F[y][x]) > p2:
                p2 = np.abs(F[y][x])

            if np.abs(F[y][x]) > p1:
                p2 = p1
                p1 = np.abs(F[y][x])

    # Reset pixels to zero using threshold
    for y in np.arange(h):
        for x in np.arange(w):
            if np.abs(F[y][x]) < p2*thresh:
                qtyFiltered = qtyFiltered + 1
                Fzero[y][x] = np.real(0)

    return (Fzero, p2*thresh, qtyFiltered)

###############################################################
########################### MAIN CODE #########################
###############################################################

# Input file name
file = str(input()).rstrip()
threshold = float(input())

# Read image
img = imageio.imread(file)

# Show image
#plt.figure(figsize=(8,8))
#plt.subplot(151)
#plt.imshow(img, cmap="gray")
#plt.axis('off')

# Compute 2D discrete fourier transform
Fimg = DFT2D(img)

# the power spectrum
#plt.subplot(152)
#plt.imshow(np.log(1+np.fft.fftshift(np.abs(Fimg))), cmap="gray")
#plt.axis('off')

# Remove values below threshold
Fzero, imgThreshold, qtyFiltered = setPixelsToZero(Fimg, threshold)

#plt.subplot(153)
#plt.imshow(np.log(1+np.fft.fftshift(np.abs(Fzero))), cmap="gray")
#plt.axis('off')

# Inverse discrete fourier transform
filtered = IDFT2D(Fzero)

#plt.subplot(154)
#plt.imshow(filtered, cmap="gray")
#plt.axis('off')

#w,h = img.shape[0:2]
#newImg = np.zeros(img.shape, dtype=np.int32)
#for y in np.arange(h):
#    for x in np.arange(w):
#        if img[y][x] != filtered[y][x]:
#            print("Diff %f %f"%(img[y][x] , filtered[y][x]))
#            newImg[y][x] = 255
#plt.subplot(155)
#plt.imshow(newImg, cmap="gray")
#plt.axis('off')
#
#plt.show()


# Show output
print("Threshold=%.4f" % (imgThreshold))
print("Filtered Coefficients=%d" % (qtyFiltered))
print("Original Mean=%.2f" % (np.mean(img)))
print("New Mean=%.2f" % (np.mean(filtered)))
