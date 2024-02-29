import math
import scipy.integrate as spi
import numpy as np

print ("The value of √π is:",math.sqrt(math.pi))

print('Single integral computed by SciPy trapezoid')
print('Integral of e^-x^2 from x=-inf to x=inf')

integrand = lambda x :   np.exp(-x*np.exp(2))
a = -10000
b = 10000
step = 1e-4

xs = np.arange(a, b, step)
ys = integrand(xs)

result = spi.trapezoid(ys, xs)
print('Result is ', result)