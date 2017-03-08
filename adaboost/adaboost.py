# -*- coding:utf-8 -*-
import numpy as np

class AdaClassifier(object):
    def __init__(self, base_classifier, stage_num=1):
        self._base_classifier = base_classifier
        self._stage_num = stage_num
        self.weights = None
        self.alpha = np.zeros(stage_num)
        self.classifiers = [None] * stage_num

    @property
    def base_classifier(self):
        return self._base_classifier

    @property
    def stage_num(self):
        return self._stage_num

    def compute_loss(self, pred_labels, true_labels, weights):
        loss = 0
        for pl, tl, w in zip(pred_labels, true_labels, weights):
            if pl != tl:
                loss += w
        return loss

    def predict_dataset(self, dataset):
        pred_labels = []
        for data in dataset:
            score = 0
            for i in xrange(self.stage_num):
                if self.classifier[i] is not None:
                    score += self.classifier[i].pred(data) * self.alpha[i]
            pred_labels.append(1 if score > 0 else 0)
        return np.array(pred_labels)

    def train(self, dataset, true_labels):
        N, H, W = dataset.shape
        self.weights = np.zeros(N) + 1.0 / N
        
        for i in xrange(self.stage_num): 
            self.classifiers[i] = self.base_classifier(1)
            self.classifiers[i].train(dataset, true_labels, self.weights)
            pred_labels = self.predict_dataset(dataset)
            loss = self.compute_loss(pred_labels, true_labels, self.weights)
            self.alpha[i] = 0.5 * np.log( (1-loss) / loss )
            equal_list = [pred_labels[i] == true_labels[i] for i in xrange(len(true_labels))]
            self.weights = self.weights * np.exp(-self.alpha[i] * (np.array([x*1 for x in equal_list]) + np.array([x-1 for x in equal_list])))
            self.weights = (self.weights - self.weights.min()) / (self.weights.max() - self.weights.min()) if self.weights.max() != self.weights.min() else np.zeros(self.weights.shape)

