# -*- coding: utf-8 -*-
import cv2
import os

if os.path.exists('dataset/pos'):
    os.system('rm -rf dataset/pos/')
os.system('mkdir dataset/pos')

if os.path.exists('dataset/neg'):
    os.system('rm -rf dataset/neg/')
os.system('mkdir dataset/neg')

with open('pos.txt','r') as f:
    for line in f:
        line = line.strip()
        img = cv2.imread(line)
        img = cv2.resize(img, (20,20))
        cv2.imwrite('dataset/pos/{}'.format(reduce(lambda x,y:x+'_'+y, line.split('/')[-2:])), img)

with open('neg.txt','r') as f:
    for line in f:
        line = line.strip()
        img = cv2.imread(line)
        img = cv2.resize(img, (20,20))
        cv2.imwrite('dataset/neg/{}'.format(line.split('/')[-1]), img)

