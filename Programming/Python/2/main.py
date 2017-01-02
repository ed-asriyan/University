# заданы т-ки `А`, прямые `В`. найти две такие т-ки из
# `А`, что проходящая через их прямая, была параллельна
# наибольшему количеству прямых

# Parsing string to list as point [x, y] and returns this
def GetCoord(s):
	coordinates = s.split(',')
	#if len(coordinates) != 2:
	#	raise Exception("Invalid number of coord")
	return [int(x) for x in coordinates]

# returns points which are read from keyboard
def InputPoints():
	s = input("Enter points (x1,y1 x2,y2 ...): ")

	result = []
	for point in s.split():
		result.append(GetCoord(point))

	if len(result) < 2:
		print("\tError: too few points")
		return InputPoints()

	return result

# returns lines whick are read from keyboard
def InputLines():
	n = int(input("Enter count of lines (positive int): "))
	if n <= 0:
		print("\tInvalid input.")
		return InputLines()

	result = []

	for i in range(n):
		s =input("Enter two points in line (x1,y1 x2,y2): ").split()

		if len(s) != 2:
			print("\tInvalid input.")
			return InputLines()

		result.append([GetCoord(x) for x in s])

	return result

# check: is line (p1, p2) || line l
def CheckPointsAndLine(p1, p2, l):
	return (p1[0] - p2[0]) * (l[0][1] - l[1][1]) == \
			(p1[1] - p2[1]) * (l[0][0] - l[1][0]) 


def GetMathLook(p1, p2):
	delX = p2[0] - p1[0]
	delY = p2[1] - p1[1]

	if delX:
		k = delY / delX
		b = p1[1] - k * p1[0]

		return "y = " + (((str(k) if k != 1 else "") + "x " +\
		 ("+ " if b else "")) if k else "") + (str(b) if b else "")
	else:
		b = p1[0]

		return "x = " + str(b);


# --------------------------------------------------------			

# read soure data
A = InputPoints()
B = InputLines()

# list of all possible combinations (point, point)
# [ [ [ x1, y1 ], [ x2, y2], count_of_||_lines ] ]
allPointsCombinationMap = []
for z in range(len(A)):
	for y in range(z + 1, len(A)):
		allPointsCombinationMap.append([A[z], A[y], 0])

# filling *count* in allPointsCombinationMap
for pp in allPointsCombinationMap:
	for line in B:
		pp[2] += CheckPointsAndLine(pp[0], pp[1], line)

# searching max value in allPointsCombinationMap by *count*
maxIndex = 0
maxValue = allPointsCombinationMap[0][2]
for i in range(len(allPointsCombinationMap)):
	if maxValue < allPointsCombinationMap[i][2]:
		maxValue = allPointsCombinationMap[i][2]
		maxIndex = i


# printing result
if maxValue:
	resPoint1 = allPointsCombinationMap[maxIndex][0]
	resPoint2 = allPointsCombinationMap[maxIndex][1]
	print("Result: ", resPoint1[0],',',resPoint1[1], sep='',end=' ')
	print(resPoint2[0], ',', resPoint2[1], sep='')
	print("Line:", GetMathLook(resPoint1, resPoint2));


	for k in allPointsCombinationMap:
		if k[2] == maxValue:
			print('\nPoints: ', k[0], ' ', k[1], sep='')
			print('Line:', GetMathLook(k[0], k[1]))

else:
	print("There are not such points.")
