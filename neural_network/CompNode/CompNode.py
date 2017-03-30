''' Nodes of computation graph '''
import numpy as np

class CompNode(object):
    ''' 
    An CompNode contains two operation: forward and backward, say
    an Add CompNode, when doing forward, it could take two numpy.ndarray, add them 
    and then output a numpy.ndarray which is the sum of them, while
    doing backward, it takes the residual of the forward output and
    return it to the forward inputs.
    Computations like addiction, substraction, sin, cos, etc.
    are included.
    '''

    # Dict to store relation between forward function and operation.Add new operations here
    symbol_dict = {
                    'data':'data',
                    '+':'add',
                    '-':'sub',
                    '*':'mul',
                    'exp':'exp',
                    'pow':'pow'
                  }
    
    def __init__(self, operation, operands=None, name=''):
        # Variables
        self._operation = operation
        self._external_forward_input = None
        self._internal_forward_input = None
        self._internal_constant = None
        self.forward_output = None
        self._name = name
        self.forward_funcs = (self.forward_data, self.forward_add, self.forward_sub, self.forward_mul, self.forward_exp, self.forward_pow)
        self.backward_funcs = (self.backward_data, self.backward_add, self.backward_sub, self.backward_mul, self.backward_exp, self.backward_pow)

        # Functions
        self._forward_func = None
        self._backward_func = None

        # Init
        if not self.parse(operation):
            raise ValueError('Operation {} has NOT been registered'.format(operation))

    @property
    def operation(self):
        return self._operation

    @property
    def external_forward_input(self):
        return self._external_forward_input

    @property
    def internal_forward_input(self):
        return self._internal_forward_input

    @property
    def internal_constant(self):
        return self._internal_constant

    @property
    def name(self):
        return self._name

    def set_forward_input(self, _input):
        self._external_forward_input = _input

    def set_internal_constant(self, _input):
        self._internal_constant = _input

    def set_forward_output(self, _output):
        self._forward_output = output

    def wrap_forward_input(self, _input):
        assert isinstance(_input, list)
        for _i in _input:
            if isinstance(_input, CompNode):
                self.set_internal_forward_input(_input.forward_output)
            else:
                self.set_internal_forward_input(_input)
        return self.internal_forward_input

    def parse(self, operation):
        found = False
        for sym, name in self.symbol_dict.items():
            if operation == sym:
                for for_func, back_func in zip(self.forward_funcs, self.backward_funcs):
                    if for_func.__name__.split('_')[-1] == name:
                        self._forward_func = for_func
                        self._backward_func = back_func
                        found = True
                        break
        return found

    def forward(self, _input=None):
        if _input == None:
            if self.external_forward_input == None:
                raise ValueError('input to CompNode {} has NOT been assigned'.format(self.name))
            _input = self.external_forward_input
        _input = self.wrap_forward_input(_input)
        self.forward_output = self._forward_func(_input)
        return self.forward_output

    def backward(self, _residual=None):
        pass


    ''' 
        Define all kinds of operations.Both forward and backward .
        Function names must be a pair of forward_xxx and backward_xxx
    '''
    # data
    def forward_data(self):
        return self.internal_forward_input

    def backward_data(self):
        pass

    # add
    def forward_add(self):
        return self.internal_forward_input + self.internal_constant

    def backward_add(self, param):
        return param

    # mul
    def forward_mul(self):
        return self.internal_forward_input * self.internal_constant

    def backward_mul(self, param):
        return param*self.input[1]

    # exp
    def forward_exp(self):
        return np.exp(self.internal_forward_input)

    def backward_exp(self, param):
        return param*self.forward_output
    
    # sub
    def forward_sub(self):
        return self.internal_forward_input - self.internal_constant

    def backward_sub(self, param):
        return param

    # pow
    def forward_pow(self):
        return np.power(self.internal_forward_input, self.internal_constant)

    def backward_pow(self, param):
        x, power = self.input
        return param*power*np.power(x, power-1) 
