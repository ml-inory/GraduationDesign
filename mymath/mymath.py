# -*- coding:utf-8 -*-
import numpy as np

def conv(filt, dataset, stride=1):
    if isinstance(dataset, list):
        dataset = np.array(dataset)
    if dataset.ndim < 3:
        dataset = dataset.reshape((1, dataset.shape[0], dataset.shape[1])) 
    f_h, f_w = filt.shape
    N, d_h, d_w = dataset.shape
    f_map_h, f_map_w = int((d_h-f_h)/stride)+1, int((d_w-f_w)/stride)+1
    f_map = np.zeros((N, f_map_h, f_map_w))
    
    for r in xrange(f_map_h):
        for c in xrange(f_map_w):
            f_map[:,r,c] = np.sum(np.tile(filt, (1,N)).reshape((N,f_h,f_w)) * dataset[:, r*stride:r*stride+f_h, c*stride:c*stride+f_w], axis=(1,2))

    return f_map
