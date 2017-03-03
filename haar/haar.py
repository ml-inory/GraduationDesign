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
