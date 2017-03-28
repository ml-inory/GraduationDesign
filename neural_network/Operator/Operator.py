''' Nodes of computation graph '''
import numpy as np

class Operator(object):
    ''' 
    An Operator contains two operation: forward and backward, say
    an Add Operator, when doing forward, it could take two numpy.ndarray, add them 
    and then output a numpy.ndarray which is the sum of them, while
    doing backward, it takes the residual of the forward output and
    return it to the forward inputs.
    Computations like addiction, substraction, sin, cos, etc.
    are included.
    '''

    # Dict to store relation between forward function and operation.Add new operations here
    symbol_dict = {
                    '+':'add',
                    '-':'sub',
                    '*':'mul',
                    'exp':'exp',
                    'pow':'pow'
                  }
    
    def __init__(self, operation, input=None):
        ''' private '''
        # Variables
        self._operation = operation
        self._residual = None

        # Functions
        self._forward_func = None
        self._backward_func = None

        ''' public '''
        # Variables
        self.forward_input = input
        self.backward_input = None
        self.forward_output = None
        self.backward_output = None
        self.forward_funcs = (self.forward_add, self.forward_sub, self.forward_mul, self.forward_exp, self.forward_pow)
        self.backward_funcs = (self.backward_add, self.backward_sub, self.backward_mul, self.backward_exp, self.backward_pow)

        # Init
        self._parse(operation)

    @property
    def operation(self):
        return self._operation

    def set_forward_input(self, _input):
        self.forward_input = _input

    def set_backward_input(self, _input):
        self.backward_input = _input

    def forward(self, _input=None):
        if _input == None:
            _input = self.forward_input
        if isinstance(_input, list):
            for i, x in enumerate(_input):
                if isinstance(x, Operator):
                    _input[i] = x.forward_output
        else:
             _input = [_input.forward_output] if isinstance(_input, Operator) else [_input]
        _input = np.array(_input)
        self.forward_output = self._forward_func(_input)
        return self.forward_output

    def backward(self, _residual=None):
        if _residual == None:
            _residual = self.backward_input
        if isinstance(_residual, list):
            for i, x in enumerate(_residual):
                if isinstance(x, Operator):
                    _residual[i] = x.backward_output
        else:
             _residual = [_residual.backward_output] if isinstance(_residual, Operator) else [_residual]
        _residual = np.array(_residual)
        self.backward_output = self._backward_func(_residual)
        return self.backward_output

    ''' Register operation functions here '''
    def _parse(self, operation):
        found = False
        for sym, name in self.symbol_dict.items():
            if operation == sym:
                for for_func, back_func in zip(self.forward_funcs, self.backward_funcs):
                    if for_func.__name__.split('_')[-1] == name:
                        self._forward_func = for_func
                        self._backward_func = back_func
                        found = True
                        break
            
        if not found:
            raise ValueError('Operation {} has NOT been registered'.format(operation))

    ''' 
        Define all kinds of operations.Both forward and backward .
        Function names must be a pair of forward_xxx and backward_xxx
    '''
    # add
    def forward_add(self, params):
        return params[0]+params[1]

    def backward_add(self, param):
        return param

    # mul
    def forward_mul(self, params):
        return params[0]*params[1]

    def backward_mul(self, param):
        return param*self.input[1]

    # exp
    def forward_exp(self, param):
        return np.exp(param)

    def backward_exp(self, param):
        return param*self.forward_output
    
    # sub
    def forward_sub(self, params):
        return params[0]-params[1]

    def backward_sub(self, param):
        return param

    # pow
    def forward_pow(self, params):
        return np.power(params[0], params[1])

    def backward_pow(self, param):
        x, power = self.input
        return param*power*np.power(x, power-1) 
