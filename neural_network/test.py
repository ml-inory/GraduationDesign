from Operator import *

def forward(x):
    op_mul1 = Operator('*', [x, -1])
    op_exp1 = Operator('exp', [op_mul1])
    op_add1 = Operator('+', [op_exp1, 1])
    op_mul1.forward()
    op_exp1.forward()        
    result = op_add1.forward()
    return result

print forward(0)
