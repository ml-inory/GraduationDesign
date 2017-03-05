# -*- coding: utf-8 -*-
import numpy as np
import cart
import haar
import mymath
import os
import cv2

# tree = cart.Tree(1)
# tree.debug()
# tree.add_layer(0.1)
# tree.debug()

#y = tree.pred(1)
#print y

#feature = haar.get_haar_feature(0, (3,9))
#print feature

# img_path = os.path.join('dataset/pos', os.listdir('dataset/pos')[0])
# img = cv2.imread(img_path, 0)
# print img.shape

# filt = haar.get_haar_template(0, (5,5)) 
# print mymath.conv(filt, img)

integral_image = haar.get_integral_image(np.ones((3,3)))
print integral_image
sum1 = haar.sum_by_integral(integral_image, (0,1), (2,2))
print sum1