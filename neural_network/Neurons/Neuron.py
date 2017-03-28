'''
    Wrap specific kinds of computations using Operator
    into a neuron.Takes multiple inputs through the 
    computation graph and returns an output.I would like
    it to take a computation expression and concat the
    Operators needed automatically,but it need more work,
    will implement it later.Right now, it's just a naive
    version
'''
import numpy as np
from Operator import Operator

class Neuron(object):
    '''
        Base Class of the other kinds of neurons such as
        ReLU, Softmax, etc.
    '''
    def __init__(self, neuron_type):
        ''' private '''
        # Variables
        self._neuron_type = neuron_type
        self._input_size = 0

        # Functions
        self._forward_func = None
        self._backward_func = None

        ''' public '''
        # Variables
        self.forward_output = None
        self.backward_output = None
        self.ops = []

        # Init
        self._parse(neuron_type)

    @property
    def neuron_type(self):
        return self._neuron_type

    @property
    def input_size(self):
        return self._input_size

    def forward(self, _input):
        self._input_size = len(_input)
        self.forward_output = self._forward_func(_input)
        return self.forward_output

    def backward(self, _input):
        self.backward_output = self._backward_func(_input)
        return self.backward_output

    ''' Register forward_func here '''
    def _parse(self, neuron_type):
        if neuron_type == 'Softmax':
            self._forward_func = self.forward_softmax
        if neuron_type == 'Debug':
            self._forward_func = self.forward_debug
        else:
            raise ValueError('Neuron type {} has NOT been registered'.format(neuron_type))

    ''' Define all kinds of operations.Both forward and backward '''
    def forward_debug(self, _input):
        # 2*(1 + x)
        op = Operator('+')
        self.ops.append(op)
