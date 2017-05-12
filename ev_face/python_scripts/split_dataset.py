# -*- coding: utf-8 -*-
# 2017/05/12/02:44PM
# author: ml-inory
# 功能：从train分割出test

import os
import sys

train_root = '../crop_dataset/train'
test_root = '../crop_dataset/test'

def main():
    # Check if train_root exists
    if not os.path.exists(train_root):
        print train_root, ' not exist.'
        return -1
    # If test_root not exist, create it
    if not os.path.exists(test_root):
        os.system('mkdir %s' % test_root)

    for src_star_name in os.listdir(train_root):
        if src_star_name[0] == '.':
            continue
        str_star_path = os.path.join(train_root, src_star_name)
        dst_star_path = os.path.join(test_root, src_star_name)
        if not os.path.exists(dst_star_path):
            os.system('mkdir %s' % dst_star_path)
        for src_img_name in os.listdir(str_star_path):
            src_img_path = os.path.join(str_star_path, src_img_name)
            img_num = int(src_img_name.split('.')[0])
            if img_num > 10:
                dst_img_path = os.path.join(dst_star_path, src_img_name)
                os.system('mv %s %s' % (src_img_path, dst_img_path))
                print 'Move %s to %s' % (src_img_path, dst_img_path)

if __name__ == '__main__':
    main()