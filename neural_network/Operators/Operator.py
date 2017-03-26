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
	def __init__(self, operation=None):
		self._operation = operation
		self.forward = None
		self.backward = None
		self._parse(self._operation)

	@property
	def operation(self):
		return self._operation

	''' Register operation functions here '''
	def _parse(self):
		if self.operation == '+':
			self.forward = self.add
		else:
			raise ValueError('Operation {} has NOT been registered'.format(self.operation))


	''' Define all kinds of operations.Both forward and backward '''
	def forward_add(self, params):
		return reduce(lambda: x,y:x+y, params)

	def backward_add(self, param):
		return [param]*input_size

