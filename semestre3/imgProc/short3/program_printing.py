'''
Short assignment 3 : Mathematical Morphology for Color Image Processing

Breno Cunha Queiroz - 11218991
Course SCC0251 - USP
07/07/2020 - semestre 3
'''
import numpy as np
import imageio
from skimage import morphology
import matplotlib.pyplot as plt
import matplotlib as mpl

###############################################################
########################### FUNCTIONS #########################
###############################################################

def rgbOpening(img, diskSize):
    imgR = img[:,:,0]
    imgG = img[:,:,1]
    imgB = img[:,:,2]

    plt.figure(figsize=(10,2))

    plt.subplot(2,4,1)
    plt.imshow(img)
    plt.axis('off')

    plt.subplot(2,4,2)
    plt.imshow(imgR, cmap='gray')
    plt.axis('off')

    plt.subplot(2,4,3)
    plt.imshow(imgG, cmap='gray')
    plt.axis('off')

    plt.subplot(2,4,4)
    plt.imshow(imgB, cmap='gray')
    plt.axis('off')

    #---------- Opening
    imgR = morphology.erosion(imgR, morphology.disk(diskSize)).astype(np.uint8)
    imgR = morphology.dilation(imgR, morphology.disk(diskSize)).astype(np.uint8)
    imgG = morphology.erosion(imgG, morphology.disk(diskSize)).astype(np.uint8)
    imgG = morphology.dilation(imgG, morphology.disk(diskSize)).astype(np.uint8)
    imgB = morphology.erosion(imgB, morphology.disk(diskSize)).astype(np.uint8)
    imgB = morphology.dilation(imgB, morphology.disk(diskSize)).astype(np.uint8)

    newImg = np.zeros(img.shape, "uint8")
    newImg[:,:,0] = imgR
    newImg[:,:,1] = imgG
    newImg[:,:,2] = imgB
    #---------- End

    plt.subplot(2,4,5)
    plt.imshow(newImg)
    plt.axis('off')

    plt.subplot(2,4,6)
    plt.imshow(imgR, cmap='gray')
    plt.axis('off')

    plt.subplot(2,4,7)
    plt.imshow(imgG, cmap='gray')
    plt.axis('off')

    plt.subplot(2,4,8)
    plt.imshow(imgB, cmap='gray')
    plt.axis('off')

    plt.show()

    return newImg

def composition(img, diskSize):
    # Convert to HSV
    imgHSV = img.copy()
    imgHSV = mpl.colors.rgb_to_hsv(imgHSV)

    # Normalize [0-255]
    currMin = np.min(imgHSV[:,:,0])
    currMax = np.max(imgHSV[:,:,0])
    n,m = imgHSV.shape[0:2]
    for y in np.arange(m):
        for x in np.arange(n):
            imgHSV[x, y, 0] = float(imgHSV[x, y, 0]-currMin)/(currMax-currMin)*255

    # Morphological gradient
    dilation = morphology.dilation(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    erosion = morphology.erosion(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    gradient = np.subtract(dilation, erosion)

    # Normalize gradient [0-255]
    currMin = np.min(gradient)
    currMax = np.max(gradient)
    n,m = gradient.shape[0:2]
    for y in np.arange(m):
        for x in np.arange(n):
            gradient[x, y] = float(gradient[x, y]-currMin)/(currMax-currMin)*255

    # Compose rgb
    result = np.zeros(img.shape)
    result[:,:,0] = gradient
    result[:,:,1] = dilation
    result[:,:,2] = erosion

    plt.figure(figsize=(10,2))
    plt.subplot(151)
    plt.imshow(imgHSV[:,:,0], cmap='hsv'); plt.title("hsv")
    plt.subplot(152)
    plt.imshow(dilation, cmap='hsv'); plt.title("dilation")
    plt.subplot(153)
    plt.imshow(erosion, cmap='hsv'); plt.title("erosion")
    plt.subplot(154)
    plt.imshow(gradient, cmap='hsv'); plt.title("gradient")
    plt.subplot(155)
    plt.imshow(result); plt.title("Result")
    plt.show()

    return result

def openingAndCompose(img, diskSize):
    opened = rgbOpening(img, 2*diskSize)
    result = composition(opened, diskSize)
    return result

def evaluate(img, newImg):
    numElements = img.shape[0]*img.shape[1]
    RMSE = np.sqrt(np.sum(np.square(np.subtract(img.astype("float"), newImg.astype("float"))))/numElements)
    print("{0:.4f}".format(RMSE,4))

###############################################################
########################### MAIN CODE #########################
###############################################################

# Input file name
file = str(input()).rstrip()
# Open image
img = imageio.imread(file)
newImg = img
# Read structuring element
k = int(input())
# Result image
option = int(input())

# Run selected transformation
if option == 1:
    newImg = rgbOpening(img, k)
elif option == 2:
    newImg = composition(img, k)
elif option == 3:
    newImg = openingAndCompose(img, k)

evaluate(img, newImg)

plt.subplot(121)
plt.imshow(img)
plt.axis('off')
plt.subplot(122)
plt.imshow(newImg)
plt.axis('off')
plt.show()
