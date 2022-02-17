from functools import reduce

# SETUP
class A:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c


objs = [A(1, 2, 3), A(1, 5, 3), A(1, 69, 420)]  # diff should yield attributes b and c
# SETUP END

result = (filtered[1][0] for filtered in filter(lambda reduce_pair: not reduce_pair[0], (reduce(lambda agg, field: (agg[0] and field == agg[1], field), fields, (True, fields[0])) for fields in (zip(*map(lambda obj: vars(obj).items(), objs))))))
print(list(result))  # ['b', 'c']
