import operator
import numpy as np


def gaussian_elimination(matrix, b=None):
    m = np.array(matrix, float)
    b = np.array(b if b else [], float)
    row_count = m.shape[0]
    if len(b) == row_count:
        temp = np.empty((m.shape[0], m.shape[1] + 1))
        temp[:, :-1] = m
        temp[:, -1] = b
        m = temp

    def max_in_column(i, first_row=-1):
        first_row = first_row if first_row > -1 else i
        return max(enumerate(m[first_row:, i], first_row),
                   key=lambda x: abs(operator.itemgetter(1)(x)))

    def make_zeros_below(subtrahend_row, subtrahend_column):
        for i, row in enumerate(m[subtrahend_row + 1:], subtrahend_row + 1):
            k = -row[subtrahend_column]
            m[i, :] = [x + k * subtrahend_x for x, subtrahend_x in zip(row, m[subtrahend_row, :])]

    for current in range(row_count):
        row_to_swap, max_element = max_in_column(current)
        if max_element == 0:
            raise Exception("Matrix is singular!")
        m[[current, row_to_swap], :] = m[[row_to_swap, current], :]
        m[current] = [x / max_element for x in m[current]]
        make_zeros_below(current, current)
    m = m[::-1, :]
    for current in range(row_count):
        make_zeros_below(current, row_count - current - 1)
    return m[::-1, -1]
