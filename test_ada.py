# -*- coding:utf-8 -*-
import adaboost
import cart
import io

img_paths, dataset, labels = io.read_dataset(['toy_dataset/pos', 'toy_dataset/neg'])
cart_ = cart.CART(1)
ada_classifier = adaboost.AdaClassifier(cart.CART, 2)
ada_classifier.train(dataset, labels)
pred_labels = ada_classifier.predict_dataset(dataset)
for img_path, pred_label, true_label in zip(img_paths, pred_labels, labels):
    print 'image {}, predict to be {}, truth is {}'.format(img_path, pred_label, true_label)
