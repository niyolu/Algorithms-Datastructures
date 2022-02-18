from functools import reduce


class Foo:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c


# diff should yield attributes b and c
objs = [Foo(1, 2, 3), Foo(1, 5, 3), Foo(1, 69, 420)]


def obj_diff(objs): return [filtered[1][0] for filtered in filter(lambda reduce_pair: not reduce_pair[0], (reduce(lambda agg, field: (agg[0] and field[1] == agg[1][1], field), fields, (True, fields[0])) for fields in (zip(*map(lambda obj: vars(obj).items(), objs)))))]


print(obj_diff(objs))  # ['b', 'c']
