from CompNode import *
import sys

def forward(x):
    data = CompNode('data', x, 'data')
    mul1 = CompNode('*', [data, -1], 'mul1')
    exp1 = CompNode('exp', [mul1], 'exp1')
    add1 = CompNode('+', [exp1, 1], 'add1')
    pow1 = CompNode('pow', [add1, -1], 'pow1')
    print mul1.forward()
    print exp1.forward()        
    print add1.forward()
    print pow1.forward()


forward(float(sys.argv[1]))
