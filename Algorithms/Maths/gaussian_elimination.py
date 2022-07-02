import numpy as np

def gaussian_elimination(A,b):
    M = np.hstack((A, b.reshape(-1, 1))).astype(np.float32)
    almost_zero = lambda x: np.abs(x) < np.finfo(np.float32).eps
    n = M.shape[0] 
    
    for i in range(n-1):    
        # swap zero-pivot if necessary
        if almost_zero(M[i, i]):
            new_pivot = np.nonzero(M[i + 1:,i])[0][0] + (i + 1)
            M[i], M[new_pivot] = M[new_pivot], M[i]
            
        # normalize with pivotal column
        norm = M[i:, i].copy().reshape(-1, 1)
        norm[almost_zero(norm)] = 1.0
        M[i:] = M[i:] / norm
        
        # ignore zero-entries in pivot column
        elim = np.nonzero(M[i+1:, i])[0] + (i + 1)
        M[elim] = M[elim] - M[i]

    
    for i in range(n-1, 0, -1):
        # if back-pivot is zero we have infinite solutions, not handled here
        assert not almost_zero(M[i, i]), "infinite solutions"
        
        # normalize with pivotal column
        norm = M[:i+1, i].copy().reshape(-1, 1)
        norm[almost_zero(norm)] = 1.0
        M[:i+1] = M[:i+1] / norm
    
        # ignore zero-entries in pivot column
        elim = np.nonzero(M[:i, i])[0]
        M[elim] = M[elim] - M[i]
        
    M[0] = M[0] / M[0, 0]
    return M[:, -1]


def array_sim(a,b):
    diff = np.abs((a-b))
    bigger = np.maximum(a,b)
    return np.nan_to_num(diff/bigger)

from time import perf_counter

def sobelTC():
    A = np.array(((10,10,110),(10,110,110),(10,10,10)))
    x = np.array([-1., 0., 1.])
    b_true = np.array((100,100,0))
    b_calc = A @ x
    print(A,x,b_true,b_calc, sep="\n")
    start_GE = perf_counter()
    result = gaussian_elimination(A,b_true)
    elapsed_GE = perf_counter() - start_GE
    
    start_np = perf_counter()
    result_np = np.linalg.solve(A,b_true)
    elapsed_np = perf_counter() - start_GE
    
    print("GE : ", elapsed_GE, "seconds")
    print("np : ", elapsed_np, "seconds")
    
    
    
    print("GE", result, x)
    print("diff", array_sim(result, x))
    try:
        np.testing.assert_array_almost_equal(x, result, decimal=5)
    except AssertionError as e:
        print(e)
        return False
    else:
        return True

def someTC(): 
    A = np.array(((14,21,11),(13,12,17),(8,9,10)))
    x = np.array((5,7,9))
    b = A@x
    print(A,x,b, sep="\n")
    start_GE = perf_counter()
    result = gaussian_elimination(A,b)
    elapsed_GE = perf_counter() - start_GE
    
    start_np = perf_counter()
    result_np = np.linalg.solve(A,b)
    elapsed_np = perf_counter() - start_GE
    
    print("GE : ", elapsed_GE, "seconds")
    print("np : ", elapsed_np, "seconds")
    print(result)
    print("GE", result, x)
    print("diff", array_sim(result, x))
    try:
        np.testing.assert_array_almost_equal(x, result, decimal=5)
    except AssertionError as e:
        print(e)
        return False
    else:
        return True

if __name__ == "__main__":
    print(sobelTC())
    print(someTC())