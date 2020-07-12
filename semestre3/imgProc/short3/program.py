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

    # Open R
    imgR = morphology.erosion(imgR, morphology.disk(diskSize)).astype(np.uint8)
    imgR = morphology.dilation(imgR, morphology.disk(diskSize)).astype(np.uint8)
    # Open G
    imgG = morphology.erosion(imgG, morphology.disk(diskSize)).astype(np.uint8)
    imgG = morphology.dilation(imgG, morphology.disk(diskSize)).astype(np.uint8)
    # Open B
    imgB = morphology.erosion(imgB, morphology.disk(diskSize)).astype(np.uint8)
    imgB = morphology.dilation(imgB, morphology.disk(diskSize)).astype(np.uint8)

    newImg = np.zeros(img.shape, "uint8")
    newImg[:,:,0] = imgR
    newImg[:,:,1] = imgG
    newImg[:,:,2] = imgB

    return newImg

def composition(img, diskSize):
    # 1- Convert to HSV
    imgHSV = img.copy()
    imgHSV = mpl.colors.rgb_to_hsv(imgHSV)

    # 2- Normalize [0-255]
    currMin = np.min(imgHSV[:,:,0])
    currMax = np.max(imgHSV[:,:,0])
    n,m = imgHSV.shape[0:2]
    for y in np.arange(m):
        for x in np.arange(n):
            imgHSV[x, y, 0] = float(imgHSV[x, y, 0]-currMin)/(currMax-currMin)*255

    # 3- Morphological gradient
    dilation = morphology.dilation(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    erosion = morphology.erosion(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    gradient = np.subtract(dilation, erosion)

    # 4- Normalize gradient [0-255]
    currMin = np.min(gradient)
    currMax = np.max(gradient)
    n,m = gradient.shape[0:2]
    for y in np.arange(m):
        for x in np.arange(n):
            gradient[x, y] = float(gradient[x, y]-currMin)/(currMax-currMin)*255

    # 5- Compose rgb
    # Opening
    opening = morphology.erosion(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    opening = morphology.dilation(opening, morphology.disk(diskSize)).astype(np.uint8)
    # Closing
    closing = morphology.dilation(imgHSV[:,:,0], morphology.disk(diskSize)).astype(np.uint8)
    closing = morphology.erosion(closing, morphology.disk(diskSize)).astype(np.uint8)

    result = np.zeros(img.shape)
    result[:,:,0] = gradient
    result[:,:,1] = opening
    result[:,:,2] = closing

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
