from typing import List

def trace(t_idx, i, P, T):
    print("T:  " + T[:t_idx] + "[" + T[t_idx] + "]" + T[t_idx + 1 :])
    p_idx = len(P) - 1 - i 
    print("P:  " + P[:p_idx] + "[" + P[p_idx] + "]" + P[p_idx + 1 :])


def boyer_moore(P: str, T: str) -> int:
    """ Boyer Moore Hopcroft bad characteristic string matching
    """
    P = P.lower().replace(".","").replace(",","").replace(" ", "")
    T = T.lower().replace(".","").replace(",","").replace(" ", "")
    n = len(T)
    m = len(P)
    idx = m - 1
    lut = preprocess(P)
    while idx < n:
        for i, x in enumerate(P[::-1]):
            t_idx = idx - i
            #trace(t_idx, i, P, T)
            if T[t_idx] == x: continue
            p_idx = m - 1 - i
            shift = max(1, lut[ord(T[t_idx]) - ord("a")][p_idx]) #TODO: figure out how we get 0 and what do to about it
            idx += shift
            break
        else:
            return idx - m + 1
    return -1


def preprocess(P: str) -> List:
    m = len(P)
    bad_chr = [[m] * m for _ in range(26)]
    for idx in range(m - 1):
        chr_idx = ord(P[idx]) - ord("a")
        bad_chr[chr_idx][idx + 1:] = [idx] * (m - idx - 1)
    return bad_chr

def TC():
    P = "aba"
    T = "skrbataaba"
    assert boyer_moore(P, T) == 7

def TC2():
        
    def show_match(text, pattern):
        print ('Text:  %s' % text)
        p = boyer_moore(pattern, text)
        print ('Match: %s%s' % ("."*p, pattern))
        print("idx ", p)
       


    text = 'abacaabadcabacabaabb'
    pattern = 'abacab'
    show_match(text, pattern)

    text = 'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.'
    pattern = 'dolor'
    show_match(text, pattern)
    show_match(text, pattern + 'e')
    # not working
     
# res = (preprocess("abcabc"))
# print(len(res), len(res[0]))
# # print(res)
# P = "aba"
# T = "skrbataaba"
# print(boyer_moore(P, T))

if __name__ == "__main__":
    TC()
    TC2()