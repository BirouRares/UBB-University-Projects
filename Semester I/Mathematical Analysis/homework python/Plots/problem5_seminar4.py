import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import math


def ComputeAlternatingSeries(pts: list, n: int):
    sum = 0
    for i in range(1, n + 1):
        elem = ((-1) ** (i + 1)) / i
        sum += elem
        pts.append(sum)


def ComputeRearrangedSeries(pts: list, n: int):  # rearrange elements of the alternating series
    sum = 1
    pts.append(sum)
    n_even = 2
    n_odd = 3
    while(n_even <= n):
        sum -= 1 / n_even
        pts.append(sum)

        sum -= 1 / (n_even + 2)
        pts.append(sum)

        sum += 1 / n_odd
        pts.append(sum)

        n_even += 4
        n_odd += 2
        if (n_even == n):
            sum -= 1 / n_even
            pts.append(sum)

    # TO BE MATHEMATICALLY ACCURATE FOR A FINITE 'N'. IF WE COMMENT IT OUT, IT WON'T DIVERGE, BUT IT WILL HAVE LESS
    # ELEMENTS
    while(n_odd <= n):
        sum += 1 / n_odd
        pts.append(sum)
        n_odd += 2


def EqualizePlots(yALTpoints, xpoints: list):  # so we don't get errors, we make the cardinals of the lists equal
    if (len(yALTpoints) > len(xpoints)):
        while (len(yALTpoints) > len(xpoints)):
            yALTpoints.pop()
    else:
        while (len(xpoints) > len(yALTpoints)):
            xpoints.pop()


def CalculateOffset(n: int):  # so it can be displayed nice :)
    if (n % 4 == 0 or n % 4 == 1):
        return 0
    elif (n % 4 == 3):
        return 1
    else:
        return 3


n = 250
offset = CalculateOffset(n)  # needed to correctly place the point of divergence

xpoints = list(range(1, n + 1))  # this is the X axis, the 'x' cardinal point, and it goes from 1 to n
ypoints = []  # this is the Y axis, the 'f(x)' cardinal point, and it is dictated by whatever the sum of the
                    # Alternating Harmonic Series is at any given 'n'
ComputeAlternatingSeries(ypoints, n)

yALTpoints = []  # this is the Y axis, the 'f(x)' cardinal, and it is dictated by whatever the sum of the
                    # Rearranged Alternating Harmonic Series is at any given 'n'
ComputeRearrangedSeries(yALTpoints, n)
EqualizePlots(yALTpoints, xpoints)  # since the computation of the Rearranged Alternating Harmonic Series might
                                        # give us more than 'n' coordinates, we shave off the extras

x_log2 = np.linspace(math.log(2, math.e), math.log(2, math.e), n)  # constant function, horizontal line that passes
                                                                        # through ln(2)
x_divlog2 = np.linspace(math.log(2, math.e) / 2, math.log(2, math.e) / 2, n)  # constant function, horizontal line
                                                                                    # that passes through ln(2) / 2

plt.subplot(2, 1, 1)  # FIRST SUBPLOT
plt.title('Graph of the Alternating Harmonic Series')
plt.plot(xpoints, ypoints, color='red', ls='-', label='Alternating Harmonic Series Graph')
plt.plot(x_log2, color='blue', ls='--', label='Constant function with f(x) equal to ln(2)')
plt.plot(x_divlog2, color='green', ls='--', label='Constant function with f(x) equal to ln(2)/2')
plt.legend()

plt.subplot(2, 1, 2)  # SECOND SUBPLOT
plt.title('Graph of the Rearranged Alternating Harmonic Series')
plt.plot(xpoints, yALTpoints, color='pink', ls='-', label='Alternating Harmonic Series Graph, with rearranged terms')
plt.plot(x_log2, color='blue', ls='--', label='Constant function with f(x) equal to ln(2)')
plt.plot(x_divlog2, color='green', ls='--', label='Constant function with f(x) equal to ln(2)/2')
plt.axvline(x=((3 * n) // 4 + offset), color='black', ls=':', label='Pt. of Divergence (cca. (3 * n) / 4), WHEN n is FINITE')
plt.legend()

'r-'

plt.show()
