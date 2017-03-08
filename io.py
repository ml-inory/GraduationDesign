# -*- coding:utf-8 -*-
import numpy as np
import cv2
import os

def read_dataset(path):
    # read images from path, path could be list 
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
    return img_paths, np.array(imgs), np.array(labels)


