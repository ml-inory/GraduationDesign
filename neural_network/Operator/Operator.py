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
                    '*':'mul',
                    'exp':'exp'
                  }
    
    def __init__(self, operation, input=None):
        ''' private '''
        # Variables
        self._operation = operation
        self._input = input
        self._input_size = 0
        self._residual = None

        # Functions
        self._forward_func = None
        self._backward_func = None

        ''' public '''
        # Variables
        self.forward_output = None
        self.backward_output = None
        self.forward_funcs = (self.forward_add, self.forward_mul, self.forward_exp)
        self.backward_funcs = (self.backward_add, self.backward_mul, self.backward_exp)

        # Init
        self._parse(operation)

    @property
    def operation(self):
        return self._operation

    @property
    def input_size(self):
        return self._input_size

    @property
    def input(self):
        return self._input

    @property
    def residual(self):
        return self._residual

    def set_input(self, _input):
        self._input_size = len(_input)
        if self._input_size > 2:
            raise ValueError('The number of operands must be less than or equal to 2')
        self._input = _input

    def set_residual(self, _residual):
        self._residual = _residual

    def forward(self, _input=None):
        if _input == None:
            _input = self.input
        else:
            self._input_size = len(_input)
            if self._input_size > 2:
                raise ValueError('The number of operands must be less than or equal to 2')

        self.forward_output = self._forward_func(_input)
        return self.forward_output

    def backward(self, _residual=None):
        if _residual == None:
            _residual = self.residual

        self.backward_output = self._backward_func(_residual)
        if isinstance(self.input[0], Operator):
            self.input[0].set_residual(self.backward_output)
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
    def _forward_check_params(self, params):
        if not isinstance(params, list):
            params = [params]
        import copy
        tmp_params = copy.deepcopy(params)
        for i, param in enumerate(params):
            if isinstance(param, Operator):
                tmp_params[i] = param.forward_output
        return tmp_params

    # add
    def forward_add(self, params):
        tmp_params = self._forward_check_params(params)
        return [reduce(lambda x,y:x+y, tmp_params)]

    def backward_add(self, param):
        return param

    # mul
    def forward_mul(self, params):
        tmp_params = self._forward_check_params(params)
        return [reduce(lambda x,y:x*y, tmp_params)]

    def backward_mul(self, param):
        return param*self.input[1]

    # exp
    def forward_exp(self, params):
        tmp_params = self._forward_check_params(params)
        return np.exp(tmp_params).tolist()

    def backward_exp(self, param):
        return param*np.exp(self.input[1]) 
