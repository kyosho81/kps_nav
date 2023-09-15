                  import os
import numpy as np
import cv2
import sys
 
im_path = sys.argv[1]
im = cv2.imread(im_path, 0)
 
if im is None:
	print im_path, " not exist"
	sys.exit()
 
ret, im = cv2.threshold(im, 127, 255, cv2.THRESH_BINARY)
element = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))
 
skel = np.zeros(im.shape, np.uint8)
erode = np.zeros(im.shape, np.uint8)
temp = np.zeros(im.shape, np.uint8)
 
i = 0
while True:
	cv2.imshow('im %d'%(i), im)
	erode = cv2.erode(im,element)
	temp  = cv2.dilate(erode, element)
 
	#消失的像素是skeleton的一部分
	temp = cv2.subtract(im, temp)
	cv2.imshow('skeleton part %d' %(i,), temp)
	skel = cv2.bitwise_or(skel, temp)
	im = erode.copy()
	
	if cv2.countNonZero(im)== 0:
		break;
	i += 1
 
cv2.imshow('Skeleton', skel)
cv2.waitKey()