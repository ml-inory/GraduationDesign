# -*- coding: utf-8 -*-
import numpy as np
import cart
import haar
import mymath
import os
import cv2
import time
import sys

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
def read_dataset(path):
    imgs = []
    labels = []
    img_paths = []
    for p in path:
        for img_path in [os.path.join(p, x) for x in os.listdir(p)]:
            img = cv2.imread(img_path, 0)
            imgs.append(img)
            if 'pos' in img_path:
                labels.append(1)
            else:
                labels.append(0)
            img_paths.append(img_path)
    return img_paths, np.array(imgs), labels

def pred(img, thresh, settings):
    feature_pos, feature_size, feature_num = settings
    integral_img = haar.get_integral_image(img)
    feature = haar.compute_haar_feature(integral_img, feature_num, feature_size, feature_pos)[0]
    if feature >= thresh:
        return 1
    else:
        return 0

img_paths, dataset, labels = read_dataset(['toy_dataset/pos','toy_dataset/neg'])
cart_ = cart.CART(3)
cart_.train(dataset, labels)        
img = cv2.imread(img_paths[0])
print cart_.pred(img), img_paths[0]
