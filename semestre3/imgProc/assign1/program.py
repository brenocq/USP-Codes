'''
Assignment 1 : intensity transformations

Breno Cunha Queiroz - 11218991
Course SCC0251 - USP
25/03/2020 - semestre 3
'''
import numpy as np
import imageio

###############################################################
########################### FUNCTIONS #########################
###############################################################

def inversion():
    global newImg
    global img
    newImg = 255-img

def contrastModulation():
    global newImg
    global img
    c = int(input())
    d = int(input())
    a = img.min()
    b = img.max()

    for x,row in enumerate(img):
        for y,col in enumerate(row):
            i = img[x][y]
            newImg[x][y] = ((i-a)*(d-c)/(b-a))+c

def logarithmicFunction():
    global newImg
    global img
    R = img.max()

    for x,row in enumerate(img):
        for y,col in enumerate(row):
            i = img[x][y]
            newImg[x][y] = 255*( np.log2(1+i)/np.log2(1+R) )

def gammaAdjustment():
    global newImg
    global img
    W = int(input())
    g = float(input())

    for x,row in enumerate(img):
        for y,col in enumerate(row):
            i = img[x][y]
            newImg[x][y] = W*np.power(i,g)

def evaluate():
    global newImg
    global img
    diff = 0
    for x,row in enumerate(img):
        for y,col in enumerate(row):
            m = float(newImg[x][y])
            r = float(img[x][y])
            diff += np.power(m-r,2)
    print("{0:.4f}".format(np.sqrt(diff),4))

###############################################################
########################### MAIN CODE #########################
###############################################################

# Input file name
file = str(input()).rstrip()
# Read image
img = imageio.imread(file)
# Result image
newImg = imageio.imread(file)

# Transformation type
T = int(input())
# Save file?
S = int(input())

# Run selected transformation
if T == 1:
    inversion()
elif T == 2:
    contrastModulation()
elif T == 3:
    logarithmicFunction()
elif T == 4:
    gammaAdjustment()

# Show image result
evaluate()

# Save image
if S == 1:
    imageio.imwrite("output_img.png",newImg)

