# -*- coding: utf-8 -*-
# 2017/05/11/03:30AM
# author: ml-inory
# 功能：获取明星名字和label的对应列表，保存在label_map.txt

import os
import sys

dataset_root = '../crop_dataset/train'
dst_txt = '../for_caffe/label_map.txt'

def main():
    if len(sys.argv) != 3:
        print 'Usage: python get_label_map.py [dataset_root] [dst_txt]'
        return -1
    dataset_root, dst_txt = sys.argv[1:]
    os.system('rm %s' % dst_txt)
    offset = 0
    for i, star_name in enumerate(os.listdir(dataset_root)):
        if not os.path.exists(os.path.join(dataset_root, star_name)) or star_name[0] == '.':
            offset += 1
            continue
        label = i - offset
        with open(dst_txt, 'a+') as f:
            print star_name, label
            f.write('%s %s\n' % (star_name, label))

if __name__ == '__main__':
    main()
