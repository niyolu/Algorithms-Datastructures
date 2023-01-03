from math import sin, pi
from typing import Iterable
import numpy as np
import matplotlib.pyplot as plt


def bisect(f, y, start, stop, eps):
    middle = (stop - start) / 2 + start
    if abs(middle - stop) <= eps and abs(middle - start) <= eps:
        return None
    y_guess = f(middle)
    if abs(y_guess - y) <= eps:
        return middle
    
    return bisect(f, y, *((middle, stop) if y_guess < y else (start, middle)), eps)


def inverse(f, y, f_range):
    inv_x = bisect(f, y, f_range[0], f_range[1], 1/10**6)
    if not inv_x:
        raise "No Solution"
    dx = f_range[1] - f_range[0]
    x = np.arange(f_range[0] - dx / 30, f_range[1] + dx / 30, 0.1)
    print(x)
    plt.plot(x, f(x))
    return inv_x


def f(X, func):
    return func(X) if not isinstance(X, Iterable) else [func(x) for x in X]


print(f"inverse at {0.5} = {inverse(f, 0.5, [0, pi/2])}")
