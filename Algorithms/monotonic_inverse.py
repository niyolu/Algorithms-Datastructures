from math import sin,pi

def bisect(f, y, start, stop, eps):
    middle = (stop - start) / 2 + start
    if abs(middle - stop) < eps and abs(middle - start) < eps:
        return None
    y_guess = f(middle)
    print(y_guess, middle)
    if abs(y_guess - y) <= eps:
        return middle
    if  y_guess < y:
        return bisect(f, y, middle, stop, eps)
   
    return bisect(f, y, start, middle, eps)
        
def inverse(f, y, f_range):
     x = bisect(f, y, f_range[0], f_range[1], 1/10**6)
     if x: return x
     print("oops")
     
def d(x):
    return sin(x)

print("inv at ", inverse(d, 0.5 , [0,pi/2]))
