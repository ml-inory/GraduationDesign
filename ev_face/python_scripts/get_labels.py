# -*- coding: utf-8 -*-
# 2017/05/11/03:39AM
# author: ml-inory
# 功能：根据crop_dataset和label_map生成caffe用的train_labels.txt

import os
import sys

dataset_root = '../crop_dataset/train'
label_map_txt = '../for_caffe/label_map.txt' # read
train_label_txt = '../for_caffe/train_labels.txt' # write +

def label_map_to_dict(label_map_txt):
    label_map = {}
    with open(label_map_txt, 'r') as f:
        for l in f:
            star_name, label = l.split(' ')[:2]
            label_map[star_name] = label

    return label_map

def main():
    if len(sys.argv) != 4:
        print 'Usage: python get_label_map.py [dataset_root] [label_map_txt] [train_label_txt]'
        return -1
    dataset_root, label_map_txt, train_label_txt = sys.argv[1:]
    
    os.system('rm %s' % train_label_txt)

    label_map = label_map_to_dict(label_map_txt)

    for star_name in os.listdir(dataset_root):
        star_path = os.path.join(dataset_root, star_name)
        if star_name[0] == '.':
            continue
        for img_name in os.listdir(star_path):
            img_path = os.path.join(star_path, img_name)
            with open(train_label_txt, 'a+') as f:
                f.write('%s %s' % (img_path, label_map[star_name]))


if __name__ == '__main__':
    main()