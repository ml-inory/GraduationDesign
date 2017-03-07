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
loss, settings, thresh = haar.find_best_feature(dataset, labels)
print 'min_loss={}'.format(loss)
print 'best_feature_num={}'.format(settings[2])
print 'best_size={}'.format(settings[1])
print 'best_pos={}'.format(settings[0])
print 'thresh={}'.format(thresh)

#settings = ((11,8), (4,2), 1)
#thresh = 0.11745
acc = 0
for img_path,img,label in zip(img_paths,dataset,labels):
    result = pred(img, thresh, settings)
    if result == label:
        acc += 1
    print 'image: {} predict to be {}, truth is {}'.format(img_path,result,label)
print acc*1.0 / len(dataset)

'''
img = (np.random.random((5,5))*10).astype('int8')
integral_img = haar.get_integral_image(img)
feature_num = 0
feature_size = (1,2)
feature_pos = (0,0)
print 'feature_num:{}\tfeature_size:{}\tfeature_pos:{}\n'.format(feature_num, feature_size, feature_pos)        
feature = haar.compute_haar_feature(integral_img, feature_num, feature_size, feature_pos)
print 'img\n',img
print 'integral_img\n',integral_img
print 'feature\n',feature[0]
'''
