# merge sort

from prettytable import PrettyTable
from random import randint
from time import time
from heapq import merge

# ------------------------------------------------------------------

def generateString(length):
	result = ""
	for i in range(length):
		result += chr(randint(48, 90))
	return result

# ------------------------------------------------------------------

def generateRandomList(size, minValue=None, maxValue=None):
	if size is None or size < 0:
		return None

	if minValue == None == maxValue:
		minValue = 0
		maxValue = size

	if minValue is None:
		minValue = maxValue - size
	if maxValue is None:
		maxValue = minValue + size

	if minValue > maxValue:
		minValue, maxValue = maxValue, minValue

	return [ randint(minValue, maxValue) for i in range(size) ]

def generateSortedList(size, minValue=None, maxValue=None, increase=True):
	if size is None or size < 0:
		return None
	if not size:
		return [ ]

	if minValue == None == maxValue:
		minValue = 0
		maxValue = size

	if minValue is None:
		minValue = maxValue - size
	if maxValue is None:
		maxValue = minValue + size

	if (minValue > maxValue and increase) or (minValue < maxValue and not increase):
		minValue, maxValue = maxValue, minValue

	return [ i for i in range(minValue, maxValue, (maxValue - minValue) // size) ]

def extendList(l):
	result = [ ]
	for item in l:
		result.append([ item, generateString(10), generateString(5) ])
	return result

# ------------------------------------------------------------------

def mergeSort(m):
	#return m.sort()
	if len(m) <= 1:
		return m

	middle = len(m) // 2
	left = m[:middle]
	right = m[middle:]

	left = mergeSort(left)
	right = mergeSort(right)

	return list(merge(left, right))

# ------------------------------------------------------------------

def checkSortedList(l, increase=True):
	if l is None:
		return None

	for i in range(len(l) - 1):
		diff = l[i + 1] - l[i]
		if diff and (diff < 0) == increase:
			return False
	return True

def measureTime(func):
	if func is None:
		return None

	beginTime = time()
	func()
	endTime = time()

	return endTime - beginTime

# ------------------------------------------------------------------

def test(sizes, sortFunc, extend=False):
	table = PrettyTable([ "List Size", "Sorted List", "Random List", "Back Sorted List" ])
	for size in sizes:
		lists = [ generateSortedList(size), generateRandomList(size), generateSortedList(size, increase=False) ]
		
		if extend:
			for l in lists:
				l = extendList(l)

		sortedTime = measureTime(lambda: sortFunc(lists[0]))
		randomTime = measureTime(lambda: sortFunc(lists[1]))
		backSortedTime = measureTime(lambda: sortFunc(lists[2]))

		table.add_row([ "%8d " % size ] + [ "%3.9f" % i for i in ( sortedTime, randomTime, backSortedTime ) ])

	print(table)

# ------------------------------------------------------------------

SIZES = ( 10000, 50, 5000 )

print("*** Lists Of Integers ***".center(60))
test(SIZES, mergeSort, False)

print()
print("*** Lists With Additional Information ***".center(60))
test(SIZES, mergeSort, True)