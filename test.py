# -*- coding: utf-8 -*-
import numpy as np
import cart
import haar

tree = cart.Tree(1)
tree.debug()
tree.add_layer(0.1)
tree.debug()

feature = haar.get_haar_feature(0, (3,9))
print feature
