from Operator import *
import sys

def forward(x):
    op_mul1 = Operator('*', [x, -1])
    op_exp1 = Operator('exp', op_mul1)
    op_add1 = Operator('+', [op_exp1, 1])
    op_pow1 = Operator('pow', [op_add1, -1])
    print op_mul1.forward()
    print op_exp1.forward()        
    print op_add1.forward()
    print op_pow1.forward()

forward(float(sys.argv[1]))
