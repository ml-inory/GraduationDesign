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

def get_integral_image(dataset):
    if dataset.ndim == 2:
        dataset = dataset.reshape((1, dataset.shape[0], dataset.shape[1]))
    N, img_h, img_w = dataset.shape
    integral_img = np.zeros(dataset.shape)
    for i in xrange(N):
        for r in xrange(img_h):
            for c in xrange(img_w):
                integral_img[i,r,c] = np.sum(dataset[i, :r+1, :c+1])
    return integral_img

def sum_by_integral(integral_img, p1, p2):
    # compute sum using integral image given upper left corner and bottom right point
    x1,y1 = p1
    x2,y2 = p2
    if x1 > x2 or y1 > y2:
        raise ValueError('any of (x1,y1) mustn\'t be bigger than (x2,y2)')
        return None
    
    sum21 = 0 if x1 == 0 else integral_img[y2,x1-1]
    sum12 = 0 if y1 == 0 else integral_img[y1-1,x2]
    sum11 = 0 if x1 == 0 or y1 == 0 else integral_img[y1-1,x1-1]
    sum22 = integral_img[y2,x2]
    return sum22 - sum12 - sum21 + sum11

def compute_haar_feature(integral_img, feature_num, feature_size, pos):
    global feature_template
    N, H, W = integral_img.shape
    template = np.array(feature_template[feature_num])
    feature_h, feature_w = feature_size
    template_h, template_w = template.shape
    slice_h, slice_w = int(feature_h / template_h), int(feature_w / template_w)
    haar_feature = np.zeros(N)
    y_offset, x_offset = pos
    for i in xrange(N):
        for r in xrange(template_h):
            for c in xrange(template_w):
                p1 = (x_offset + c*slice_w, y_offset + r*slice_h)
                p2 = (p1[0] + slice_w - 1, p1[1] + slice_h - 1)
                haar_feature[i] += sum_by_integral(integral_img[i], p1, p2) * template[r,c]
    return haar_feature

def compute_loss(features, labels):
    # t1: 全部人脸样本的权重的和
    # t0: 全部非人脸样本的权重的和
    # s1: 在此元素之前的人脸样本的权重的和
    # s0: 在此元素之前的非人脸样本的权重的和
    # 分类误差: r = min((s1 + (t0 - s0)), (s0 + (t1 - s1)))
    features = np.linalg.norm(features)
    sorted_idx = np.argsort(-features)
    labels = labels[sorted_idx]
    t1 = np.sum(features[labels==1])
    t0 = np.sum(features[labels==0])

    r = []
    for idx, feature in enumerate(features):
        if 0 in labels[:idx] and 1 in labels[:idx]:
            s1 = np.sum(features[labels[:idx]==1])
            s0 = np.sum(features[labels[:idx]==0])

            r.append(np.min((s1 + (t0 - s0)), (s0 + (t1 - s1))))
    return r

def find_best_feature(dataset):
    pass
