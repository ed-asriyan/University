from gaussian_elimination import gaussian_elimination
from numpy import poly1d


class Approximator(object):
    def __init__(self, xs=None, ys=None, ros=None, polynomial_degree=1,
                 function=lambda x, p: x ** p):
        self.xs = xs if xs else [0, 0]
        self.ys = ys if ys else [0, 0]
        self.ros = ros if ros else [1, 1]
        self.polynomial_degree = polynomial_degree
        self.function = function

    def __scalar_product(self, f1, f2):
        result = 0
        for x, ro in zip(self.xs, self.ros):
            result += f1(x) * f2(x) * ro
        return result

    def linear_least_squares_coefficients(self):
        matrix_to_find_a_coefficients = []
        n = self.polynomial_degree
        b = []
        for m in range(n + 1):
            row = []
            for k in range(n + 1):
                row.append(self.__scalar_product(
                    lambda x: self.function(x, m),
                    lambda x: self.function(x, k))
                )
            matrix_to_find_a_coefficients.append(row)
            b.append(self.__scalar_product(
                lambda x: self.ys[self.xs.index(x)],
                lambda x: self.function(x, m))
            )
        return gaussian_elimination(matrix_to_find_a_coefficients, b)

    def linear_least_squares(self, point_count=256):
        p = poly1d(self.linear_least_squares_coefficients()[::-1])
        x_from, x_to = min(self.xs), max(self.xs)
        dx = (x_to - x_from) / (point_count - 1)
        x = x_from
        xs, ys = [], []
        for i in range(point_count):
            xs.append(x)
            ys.append(p(x))
            x += dx
        return xs, ys
