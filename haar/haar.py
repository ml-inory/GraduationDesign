# -*- coding:utf-8 -*-
'''
    Generate haar-like features
'''
import numpy as np
from collections import defaultdict

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

def find_index(src, msk=None):
    """
    Example using defaultdict to group value indexes with optional mask
    """
    ddl = defaultdict(list)

    for idx, val in enumerate(src):
        if msk is not None and val != msk:
            continue
        ddl[val].append(idx)
    return ddl[msk]

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

def compute_loss(features, labels, weights=None):
    # t1: 全部人脸样本的权重的和
    # t0: 全部非人脸样本的权重的和
    # s1: 在此元素之前的人脸样本的权重的和
    # s0: 在此元素之前的非人脸样本的权重的和
    # 分类误差: r = min((s1 + (t0 - s0)), (s0 + (t1 - s1)))
#    print 'features.shape:', features.shape
    norm_features = np.array((features - np.min(features)) / (np.max(features) - np.min(features)))
    sorted_idx = np.argsort(-features) # 降序排序
    labels = np.array(labels)[sorted_idx]
    norm_features = norm_features[sorted_idx]
    features = features[sorted_idx]

    pos_idx = find_index(labels, 1)
    neg_idx = find_index(labels, 0)
    
    t1 = np.sum(norm_features[pos_idx])
    t0 = np.sum(norm_features[neg_idx])

    r = []
    for idx, feature in enumerate(features):
        s0 = 0
        s1 = 0
        if 0 in labels[:idx]:
            neg_idx = find_index(labels[:idx], 0)
            s0 = np.sum(norm_features[neg_idx])
        if 1 in labels[:idx]:
            pos_idx = find_index(labels[:idx], 1)
            s1 = np.sum(norm_features[pos_idx])
        r.append(min(s1+t0-s0, s0+t1-s1))
    # print min(r)
    r = np.array(r) * weights if weights is not None else np.array(r)
    return np.min(r), features[np.argmin(r)]

def find_best_feature(dataset, labels, weights=None, stop_loss=0, debug=False):
    if dataset.ndim == 2:
        dataset = dataset.reshape((1,dataset.shape[0],dataset.shape[1]))
    N, H, W = dataset.shape
    integral_imgs = get_integral_image(dataset)
#    print 'integral_imgs.shape:',integral_imgs.shape
    global feature_template
    min_loss = None
    for f_num in xrange(len(feature_template)): # 模板种类
        cur_template = np.array(feature_template[f_num])
        template_h, template_w = cur_template.shape
        scale_max_h, scale_max_w = int(H / template_h), int(W / template_w)
        feature_min_loss = None                                        
        for scale_h in xrange(scale_max_h): # 大小
            for scale_w in xrange(scale_max_w):
                feature_h = (scale_h+1) * template_h
                feature_w = (scale_w+1) * template_w
                feature_size = (feature_h, feature_w)
                for y in xrange(H-feature_h+1):
                    for x in xrange(W-feature_w+1):
                        pos = (y,x)
                        haar_features = compute_haar_feature(integral_imgs, f_num, feature_size, pos)
                        loss, thresh = compute_loss(haar_features, labels, weights)
                        
                        if min_loss == None:
                            min_loss = loss
                            best_pos = pos
                            best_size = feature_size
                            best_feature_num = f_num
                            best_thresh = thresh
                            best_features = haar_features
                        if loss < min_loss:
                            min_loss = loss
                            best_pos = pos
                            best_size = feature_size
                            best_feature_num = f_num
                            best_thresh = thresh
                            best_features = haar_features

                        if feature_min_loss == None:
                            feature_min_loss = loss
                            print 'feature {}: pos={} size={} loss={}'.format(f_num+1, pos, feature_size, feature_min_loss)
                        if loss < feature_min_loss:
                            feature_min_loss = loss
                            print 'feature {}: pos={} size={} loss={}'.format(f_num+1, pos, feature_size, min_loss)

                        if debug:
                            break
                            #return loss, (pos, feature_size, f_num), thresh
                            
        if min_loss <= stop_loss:
            break
    left_dataset = np.array(dataset)[best_features > best_thresh]
    left_labels = np.array(labels)[best_features > best_thresh]
    return min_loss, (best_pos, best_size, best_feature_num), best_thresh, left_dataset, left_labels
