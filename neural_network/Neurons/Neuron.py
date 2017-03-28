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
        self._input_size = 0

        # Functions
        self._forward_func = None
        self._backward_func = None

        ''' public '''
        # Variables
        self.forward_input = []
        self.backward_input = []
        self.forward_output = []
        self.backward_output = []
        
        # TODO: define the computation graph here
        self.op_flow = {
            'add1':Operator('+', [])
        }

        # Init
        self._parse(neuron_type)

    def forward(self, _input):
        self.forward_output = []
        for _i in _input:
            self.forward_output.append(self._forward_func(_i))
        return self.forward_output

    def backward(self, _input):
        self.backward_output = []
        for _i in _input:
            self.backward_output.append(self._backward_func(_i))
        return self.backward_output

    ''' Define all kinds of operations.Both forward and backward '''
    def forward_debug(self, _input):
        # 2*(1 + x)
        op1 = Operator('+', [_input, 1])
        op2 = Operator('*', [op1, 2])
        
