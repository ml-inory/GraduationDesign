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
	def __init__(self):
