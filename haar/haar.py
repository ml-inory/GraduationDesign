# -*- coding:utf-8 -*-
'''
    Generate haar-like features
'''
import numpy as np

feature_template = (
            [[-1,1]],
            [[1,-1]],
            [[-1,2,1]],
            [[1,-2,1]],
            [[-1],[1]],
            [[1],[-1]],
            [[-1],[2],[-1]],
            [[1],[-2],[1]],
            [[1,-1],[-1,1]],
            [[-1,1],[1,-1]],
            [[1,1,1],[1,-8,1],[1,1,1]],
            [[-1,-1,-1],[-1,8,-1],[-1,-1,-1]]
            )

def get_haar_template(template_num, size):
    global feature_template
    template = np.array(feature_template[template_num])
    t_h, t_w = template.shape
    f_h, f_w = size
    slice_h, slice_w = int(f_h / t_h), int(f_w / t_w)
    feature = np.zeros((slice_h*t_h, slice_w*t_w))
    for r in xrange(t_h):
        for c in xrange(t_w):
            feature[r*slice_h : (r+1)*slice_h, c*slice_w : (c+1)*slice_w].fill(template[r,c])
    return feature

def get_integral_image(img):
    img_h, img_w = img.shape
    integral_img = np.zeros(img.shape)
    for r in xrange(img_h):
        for c in xrange(img_w):
            integral_img[r,c] = np.sum(img[:r+1, :c+1])
    return integral_img

def sum_by_integral(integral_img, p1, p2):
    # compute sum using integral image given upper left corner and bottom right point
    x1,y1 = p1
    x2,y2 = p2
    if x1 > x2 or y1 > y2:
        raise ValueError('any of (x1,y1) mustn\'t be bigger than (x2,y2')
        return None
    
    sum21 = 0 if x1 == 0 else integral_img[y2,x1-1]
    sum12 = 0 if y1 == 0 else integral_img[y1-1,x2]
    sum11 = 0 if x1 == 0 or y1 == 0 else integral_img[y1-1,x1-1]
    sum22 = integral_img[y2,x2]
    return sum22 - sum12 - sum21 + sum11