# -*- coding:utf-8 -*-
'''
    CART classification tree
           ----
           |f1|
           ----
           /   \
        ----    -1
     1  |f2|    
        ----    
        /   \
      ----  -1
    1 |f3|
      ----
    author: inory
    date: 2017/03/03
'''
import numpy as np
import mymath
from haar import *

class Node(object):
    def __init__(self, thresh=0, is_leaf=False):
        self._thresh = None
        self._operation = None
        self._left_node = None
        self._right_node = None
        self._is_leaf = is_leaf
        self._value = 0

    @property
    def thresh(self):
        return self._thresh

    @property
    def left_node(self):
        return self._left_node

    @property
    def right_node(self):
        return self._right_node

    @property
    def is_leaf(self):
        return self._is_leaf
    
    @property
    def value(self):
        if self.is_leaf:
            return self._value
        else:
            raise AttributeError('Only leaf nodes have attribute VALUE')

    def set_left_node(self, node):
        self._left_node = node

    def set_right_node(self, node):
        self._right_node = node

    def set_operation(self, op_func):
        if not self.is_leaf:
            self._operation = op_func
        else:
            raise AttributeError('Leaf node cannot set operation')
    
    def set_thresh(self, thresh):
        self._thresh = thresh

    def operate(self, data):
        # compute score using self._operation,
        # so remember to registry the operation function
        if self._operation is not None:
            return self._operation(data)

    def pred(self, data):
        if self.operate(data) > self.thresh:
            return self.left_node.value if self.left_node.is_leaf else self.left_node
        else:
            return self.right_node.value if self.right_node.is_leaf else self.right_node




class LeftLeaf(Node):
    def __init__(self, is_leaf=True):
        super(LeftLeaf, self).__init__(None, is_leaf)
        self._value = 1




class RightLeaf(Node):
    def __init__(self, is_leaf=True):
        super(RightLeaf, self).__init__(None, is_leaf)
        self._value = -1




class CART(object):
    def __init__(self, depth=1):
        if depth < 1:
            raise ValueError('depth must be larger or equal to 1')

        self._depth = depth
        self.head_node = Node(0)
        self.head_node.set_left_node(LeftLeaf())
        self.head_node.set_right_node(RightLeaf())
        for i in xrange(self._depth-1):
            self.add_layer(0)

    @property
    def depth(self):
        return self._depth

    def get_bottom_node(self):
        cur_node = self.head_node
        while not cur_node.left_node.is_leaf:
            cur_node = self.head_node.left_node
        return cur_node

    def add_layer(self, thresh):
        bottom_node = self.get_bottom_node()
        bottom_node.set_left_node(Node(thresh))
        cur_node = bottom_node.left_node
        cur_node.set_left_node(LeftLeaf())
        cur_node.set_right_node(RightLeaf())
        self._depth += 1

    def train(self, dataset, labels):
        for i in xrange(self.depth):
            loss, settings, thresh, dataset, labels = haar.find_best_feature(dataset, labels)
            pos, size, f_num = settings
            operation = lambda x:haar.compute_haar_features(haar.get_integral_image(x), f_num, size, pos)
            if i == 0:
                cur_node = self.head_node
            else:
                cur_node = cur_node.left_node
            cur_node.set_thresh(thresh)
            cur_node.set_operation(operation)

    def pred(self, x):
        cur_node = self.head_node
        y = cur_node.pred(x)
        while not isinstance(y, int):
            cur_node = cur_node.left_node
            y = cur_node.pred(x)
        return y
