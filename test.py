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

data = (np.random.random((3,3))*100).astype('uint8')
print 'data:\n', data
integral_image = haar.get_integral_image(data)
#sum1 = haar.sum_by_integral(integral_image, (0,1), (2,2))
#print sum1
haar_feature = haar.compute_haar_feature(integral_image, 4, (2,1), (0,0))
print 'haar_feature\n', haar_feature
