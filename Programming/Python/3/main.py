# search for the roots by secants method

import numpy, matplotlib
import matplotlib.pyplot as plt
from prettytable import PrettyTable
from math import *

# ------------------------------------------------------------------

# def f1(x):
# 	return math.sin(x) * math.cos(x / 20) * math.cos(x / 80)
# 	#return 1 / abs(x) if abs(x) > 1 else 2 - x * x
# 	#return math.e * math.sin(x / 100) / \
# 	#(abs(math.log(abs(math.sin(x) + 1))) + 1) - 1

# def f2(x):
# 	return math.sin(x / 65) * 0.43 - 0.4
# 	return x / 300

def derivative(func, x, power=1):
	dx = 0.001
	derivFunc = lambda x: (func(x + dx) - func(x)) / dx
	if power == 1:
		return derivFunc(x)
	elif power > 1:
		return derivative(derivFunc, x, power - 1)

# ------------------------------------------------------------------

# [ root, f(root), iterations, error ]
def findRootBySecants(func, p1, p2, eps, nMax):
	n = 1
	error = None

	while abs(func(p2)) > eps and abs(p1 - p2) > eps:
		if n > nMax:
			error = "Maximim of n"
			break

		fX1 = func(p1)
		fX2 = func(p2)

		if fX1 == fX2:
			error = "Horisontal"
			break
		
		if abs(fX1) < abs(fX2):
			fX1, fX2 = fX2, fX1
			p2, p1 = p1, p2

		p1, p2 = p2, p2 - (p2 - p1) * fX2 / (fX2 - fX1)

		n += 1

	return [ p2, func(p2), n, error ]

# [ №, A, B, root, f(root), iterations, error ]
def findRoots(func, a, b, step, eps, nMax):
	result = []
	aNext = min(a + step, b)
	i = 1
	lastRoot = None
	while True:
		if func(a) * func(aNext) <= 0:
			r = findRootBySecants(func, a, aNext, eps, nMax)

			# error handling
			if not r[0] is None:
				if not lastRoot is None and abs(lastRoot - r[0]) < eps:
					r[3] = "Dublicate"
				elif not (a <= r[0] <= aNext):
					r[3] = "Out of interval"
				else:
					lastRoot = r[0]

			if not r[0] is None or not r[3] is None:
				result.append([i, a, aNext] + r)
				i += 1
		a += step;
		if aNext >= b:
			break
		aNext = min(aNext + step, b)

	return result

def findExtremums(func, a, b, step, eps, nMax, power=1):
	result = findRoots(lambda x: derivative(func, x, power), a, b, step, eps, nMax)
	for i in result:
		i[4] = func(i[3])
	return result

# ------------------------------------------------------------------

def findIntersactionPoints(func1, func2, a, b, step, eps, nMax):
	return [ i[3] for i in findRoots(lambda x: func1(x) - func2(x), \
		a, b, step, eps, nMax) ]

# ------------------------------------------------------------------

def getIntegral(func, a, b, intervLength=1e-2):
	result = 0
	while a < b:
		aNext = min(a + intervLength, b)

		result += (func(a) + func(aNext)) * (aNext - a) / 2

		a += intervLength
	return result

# ------------------------------------------------------------------

def drawRoots(roots, col="red"):
	result, = plt.plot([i[3] for i in roots if not i[3] is None], \
		[i[4] for i in roots if not i[3] is None], 'ro', color=col)
	return result

def drawGraph(func, xRange, col="blue"):		
	plt.grid(True)
		
	graph, = plt.plot(xRange, [ func(x) for x in xRange ], \
		linewidth=3, color=col)

	return graph

def drawExtremums(ext, col="green"):
	result, = plt.plot([i[3] for i in ext if not i[3] is None], \
		[i[4] for i in ext if not i[3] is None], 'ro', color=col)
	return result

def drawInflections(infl, col="black"):
	result, = plt.plot([i[3] for i in infl if not i[3] is None], \
		[i[4] for i in infl if not i[3] is None], 'ro', color=col)
	return result

def drawIntervals(func1, func2, intersactPoints, eps):
	if not intersactPoints: return
	last = intersactPoints[0]
	for point in intersactPoints[1:]:
		xRange = numpy.arange(last, point, 0.001)
		plt.fill_between(xRange, [ func1(x) for x in xRange ],\
		 [ func2(x) for x in xRange ], color='blue', alpha=.1)

	result, = plt.plot(intersactPoints, [func1(point) for point in intersactPoints]\
		, 'ro', color="pink")

	return result

def showPlot():
	plt.show()

# ------------------------------------------------------------------

def printRoots(roots):
	table = PrettyTable(["№", "A", "B", "Root", "f(x)",\
	 "Loops Count", "Error"])

	for i in roots:
		if not i[6] is None:
			i[3] = None
			i[4] = None

		n = i[0]
		A = "{:.3f}".format(i[1])
		B = "{:.3f}".format(i[2])
		root = "{:7f}".format(i[3]) if not (i[3] is None) else '-'
		fx = "{:3e}".format(i[4]) if not (i[4] is None) else '-'
		loops = i[5] if not (i[5] is None) else '-'
		error = i[6]

		table.add_row([ n, A, B, root, fx, loops, error])
	
	print(table)

# ------------------------------------------------------------------

f1Code = input("Enter first  math function: f(x) = ")
f2Code = input("Enter second math function: f(x) = ")

f1 = lambda x: eval(f1Code)
f2 = lambda x: eval(f2Code)

print()

x1 = float(input("Enter the first point  (float): "))
while True:
	x2 = float(input("Enter the second point (float): "))
	if x1 < x2:
		break
	else:
		print("\tError: x1 must be less then x2.")
while True:
	eps = float(input("Enter epsilon (float): "))
	if eps > 0:
		break
	else:
		print("\tError: value must be positive.")
while True:
	step = float(input("Enter step (float): "))
	if 0 < step:
		break
	else:
		print("\tError: value must be positive.")
while True:
	nMax = float(input("Enter max n (integer): "))
	if 0 < nMax:
		break
	else:
		print("\tError: value must be positive.")

xRange = numpy.arange(x1, x2, 0.001)

roots1 = findRoots(f1, x1, x2, step, eps, nMax)
extem1 = findExtremums(f1, x1, x2, step, eps, nMax)
infle1 = findExtremums(f1, x1, x2, step, eps, nMax, 2)

roots2 = findRoots(f2, x1, x2, step, eps, nMax)
extem2 = findExtremums(f2, x1, x2, step, eps, nMax)
infle2 = findExtremums(f2, x1, x2, step, eps, nMax, 2)

intersactions = findIntersactionPoints(f1, f2, x1, x2, step, eps, nMax)
square = sum([ abs(getIntegral(lambda x: f1(x) - f2(x), intersactions[i], \
	intersactions[i + 1])) for i in range(len(intersactions) - 1)] )

graph1Obj = drawGraph(f1, xRange, "blue")
extem1Obj = drawExtremums(extem1)
infle1Obj = drawInflections(infle1)
roots1Obj = drawRoots(roots1)

graph2Obj = drawGraph(f2, xRange, "orange")
extem2Obj = drawExtremums(extem2)
infle2Obj = drawInflections(infle2)
roots2Obj = drawRoots(roots2)

intervalsObj = drawIntervals(f1, f2, intersactions, eps)
print()
printRoots(roots1)

# некрасиво, т.к. использую матплотлиб из вне функций
plt.title("Area: " + str(square))
plt.legend([ graph1Obj, graph2Obj, roots1Obj, extem1Obj, infle1Obj, intervalsObj ], \
	[ "$f1(x) = " + f1Code + "$", "$f2(x) = " + f2Code + "$", "$Roots$", "$Extremums$", "$Inflections$", "$Intersections$"])

showPlot()