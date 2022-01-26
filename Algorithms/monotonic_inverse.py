from math import sin,pi
import numpy as np
import matplotlib.pyplot as plt


aiwngfsoigna sg

def bisect(f, y, start, stop, eps):
    middle = (stop - start) / 2 + start
    if abs(middle - stop) <= eps and abs(middle - start) <= eps:
        return None
    y_guess = f(middle)
    print(y_guess, middle)
    if abs(y_guess - y) <= eps:
        return middle
    if  y_guess < y:
        return bisect(f, y, middle, stop, eps)
    else:
        return bisect(f, y, start, middle, eps)
        
def inverse(f, y, f_range):
     inv_x = bisect(f, y, f_range[0], f_range[1], 1/10**6)
     if not inv_x: raise "No Solution"
     solution = (inv_x, f(inv_x))
     dx = f_range[1] - f_range[0]
     x = np.arange(f_range[0] - dx / 30, f_range[1] + dx / 30, 0.1)
     plt.plot(x, f(x))
     return inv_x
     
def f(x):
    return sin(x)

print("inv at ", inverse(f, 0.5 , [0,pi/2]))
