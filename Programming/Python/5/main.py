from tkinter import *
from math import cos, sin, pi

class PictureFrame(Frame):
	def __init__(self):
		self.root = Tk()

		Frame.__init__(self, self.root)

		self._initUI()

	windowHeight = 500
	windowWidth  = 500

	# --- Ulils ----------------------------------------------------

	def _frange(self, begin, end, step):
		while begin <= end:
			yield begin
			begin += step

	# --- Drwing ---------------------------------------------------

	def _drawLawn(self):
		self.canvas.create_rectangle(0, 200, self.windowWidth, self.windowHeight,\
			outline="lawn green", fill="lawn green")

	def _drawSky(self):
			self.canvas.create_rectangle(0, 200, self.windowWidth, 0,\
				outline="sky blue", fill="sky blue")

	def _drawHome(self, pos):
		wallHeigth = 100
		wallLength = 100
		wallRatio  = wallHeigth / wallLength

		frontWidth  = 100
		frontHeight = 100

		roofHeight = 80

		tubeHeight = 100
		tubeWidth  = 16

		tubeOffset     = 20
		wallTubeLength = 5

		frontLabel = "BMSTU"

		houseColor      = "darkgoldenrod"
		roofColor       = "firebrick3"
		roofCircleColor = "white"
		doorColor       = "white"
		tubeColor       = "brown"
		windowColor     = "blue"

		outlines        = "black"

		# front side
		frontLeftBottom  = pos
		frontRightBottom = [ pos[0] + frontWidth, pos[1] ]
		frontLeftTop     = [ pos[0], pos[1] - frontHeight ]
		frontRightTop    = [ pos[0] + frontWidth, pos[1] - frontHeight ]

		self.canvas.create_rectangle(frontLeftBottom[0], frontLeftBottom[1],\
									 frontRightTop[0], frontRightTop[1],\
									 outline=outlines, fill=houseColor)

		# tube
		frontTubeLeftBottom = [ frontLeftTop[0] + tubeOffset, frontLeftTop[1] ]
		frontTubeRightTop   = [ frontTubeLeftBottom[0] + tubeWidth, frontTubeLeftBottom[1] - tubeHeight ]
		self.canvas.create_rectangle(frontTubeLeftBottom[0], frontTubeLeftBottom[1],\
									 frontTubeRightTop[0], frontTubeRightTop[1],\
									 outline=outlines, fill=tubeColor)

		# front roof
		roofFrontLeftBottom  = frontLeftTop
		roofFrontRightBottom = frontRightTop
		roofFrontTop         = [ (frontRightTop[0] + frontLeftTop[0]) / 2, frontLeftTop[1] - roofHeight ]

		self.canvas.create_polygon(roofFrontRightBottom[0], roofFrontRightBottom[1],
								   roofFrontLeftBottom[0], roofFrontLeftBottom[1], 
								   roofFrontTop[0], roofFrontTop[1],\
								   outline=outlines, fill=roofColor)

		# front roof circle
		roofFrontCircle = [ roofFrontTop[0], (roofFrontTop[1] + roofFrontLeftBottom[1]) / 2 ]
		roofFrontCircleRadius = 17
		self.canvas.create_oval(roofFrontCircle[0] - roofFrontCircleRadius, roofFrontCircle[1] - roofFrontCircleRadius,\
								roofFrontCircle[0] + roofFrontCircleRadius, roofFrontCircle[1] + roofFrontCircleRadius,\
								outline=outlines, fill=roofCircleColor)
	
		# wall side
		wallLeftBottom  = frontRightBottom
		wallRightBottom = [ wallLeftBottom[0] + wallLength, wallLeftBottom[1] - wallHeigth ]
		wallLeftTop     = frontRightTop
		wallRightTop    = [ wallLeftTop[0] + wallLength, wallLeftTop[1] - wallHeigth ]

		self.canvas.create_polygon(wallLeftBottom[0], wallLeftBottom[1],\
								   wallRightBottom[0], wallRightBottom[1],\
								   wallRightTop[0], wallRightTop[1],\
								   wallLeftTop[0], wallLeftTop[1], 
								   outline=outlines, fill=houseColor)

		# wall roof
		roofWallLeftBottom  = frontRightTop
		roofWallLeftTop     = roofFrontTop
		roofWallRightBottom = [ roofWallLeftBottom[0] + wallLength, roofWallLeftBottom[1] - wallHeigth ]
		roofWallRightTop    = [ roofWallLeftTop[0] + wallLength, roofWallLeftTop[1] - wallHeigth ]

		self.canvas.create_polygon(roofWallLeftBottom[0], roofWallLeftBottom[1],\
								   roofWallLeftTop[0], roofWallLeftTop[1],\
								   roofWallRightTop[0], roofWallRightTop[1],\
								   roofWallRightBottom[0], roofWallRightBottom[1],\
								   outline=outlines, fill=roofColor)

		# door
		doorLeftBottom  = [ frontRightBottom[0] - frontWidth / 2, frontRightBottom[1] ]
		doorRightBottom = [ frontRightBottom[0] - frontWidth / 8, frontRightBottom[1] ]
		doorLeftTop     = [ doorLeftBottom[0], doorLeftBottom[1] - 5 * frontHeight / 7 ]
		doorRigthTop    = [ doorRightBottom[0], doorRightBottom[1] - 5 * frontHeight / 7 ]

		self.canvas.create_polygon(doorRightBottom[0], doorRightBottom[1],\
								   doorRigthTop[0], doorRigthTop[1],\
								   doorLeftTop[0], doorLeftTop[1],\
								   doorLeftBottom[0], doorLeftBottom[1],\
								   outline=outlines, fill=doorColor)

		# doorhandle
		doorhandleBottom = [ doorLeftBottom[0] + (doorRightBottom[0] - doorLeftBottom[0]) / 3, doorLeftBottom[1] + 2 * (doorLeftTop[1] - doorLeftBottom[1]) / 5 ]
		doorhandleTop    = [ doorhandleBottom[0], doorLeftBottom[1] + 3 * (doorLeftTop[1] - doorLeftBottom[1]) / 5 ]

		self.canvas.create_line(doorhandleBottom[0], doorhandleBottom[1],\
								doorhandleTop[0], doorhandleTop[1],\
								fill=outlines)

		# front window
		windowFrontLeftBottom = [ frontLeftBottom[0] + frontWidth / 7, frontLeftBottom[1] - 2 * frontHeight / 7 ]
		windowFrontRightTop   = [ frontLeftBottom[0] + 3 * frontWidth / 7, frontLeftBottom[1] - 4 * frontHeight / 7 ]
		self.canvas.create_rectangle(windowFrontLeftBottom[0], windowFrontLeftBottom[1],\
									 windowFrontRightTop[0], windowFrontRightTop[1],\
									 outline=outlines, fill=windowColor)

		# wall window
		# wallLeftWindowHeight  = 10
		# wallLeftWindowWidth   = 15

		# wallRightWindowHeight = 5
		# wallRightWindowWidth  = 5

		# wallLeftWindowLeftTop    = [ frontRightBottom[0] + 2 * wallLength / 7, frontRightTop[1] ]
		# wallLeftWindowLeftBottom = [ wallLeftWindowLeftTop[0], wallLeftWindowLeftTop[1] + wallLeftWindowHeight ]


		# front text
		frontText = [ frontLeftTop[0] + 3.2 * frontHeight / 7, frontLeftTop[1] + 1 * frontWidth / 7 ]
		self.canvas.create_text(frontText[0], frontText[1],\
								text=frontLabel)

		# TODO ...


	def _drawKamakin(self, pos):
		skin = "black"
		label = "Kamakin"

		width       = 20
		legsHeight  = 20
		bodyHeight  = 20
		headSize    = 15

		leftBottom     = pos
		rightBottom    = [ pos[0] + width, pos[1] ]
		kek            = [ leftBottom[0] + width / 2, leftBottom[1] - legsHeight ]
		bodyTop        = [ kek[0], kek[1] - bodyHeight ]
		leftArmBottom  = [ leftBottom[0], kek[1] ]
		rightArmBottom = [ rightBottom[0], kek[1] ]
		headCenter     = [ bodyTop[0], bodyTop[1] - headSize ]
		text           = [ headCenter[0], headCenter[1] - headSize - headSize / 1.6]

		self.canvas.create_line(leftBottom[0], leftBottom[1],\
								kek[0], kek[1],\
								fill=skin)
		self.canvas.create_line(rightBottom[0], rightBottom[1],\
								kek[0], kek[1],\
								fill=skin)
		self.canvas.create_line(kek[0], kek[1],\
								bodyTop[0], bodyTop[1],\
								fill=skin)
		self.canvas.create_line(bodyTop[0], bodyTop[1],\
								leftArmBottom[0], leftArmBottom[1],
								fill=skin)
		self.canvas.create_line(bodyTop[0], bodyTop[1],\
								rightArmBottom[0], rightArmBottom[1],\
								fill=skin)
		self.canvas.create_oval(headCenter[0] - headSize, headCenter[1] - headSize,\
								headCenter[0] + headSize, headCenter[1] + headSize,\
								outline=skin)
		self.canvas.create_text(text[0], text[1],\
								text=label)


	def _drawRocket(self, pos):

		outlines      = "black"
		bodyColor     = "yellow"
		triangleColor = "green"
		wingColor     = "brown"
		windowColor   = "white"
		headColor     = "red"

		bodyWidth  = 60
		bodyHeight = 150
		
		triangleOffset = 10
		triangleHeight = 20

		wingWidth  = 30
		wingHeight = 100
		wingTransf = 15

		windowSize = bodyWidth / 4

		headHeight = 45

		# body
		bodyLeftBottom  = pos
		bodyLeftTop     = [ pos[0], pos[1] - bodyHeight ]
		bodyRightBottom = [ pos[0] + bodyWidth, pos[1] ]
		bodyRightTop    = [ pos[0] + bodyWidth, pos[1] - bodyHeight ]

		self.canvas.create_rectangle(bodyLeftBottom[0], bodyLeftBottom[1],\
									 bodyRightTop[0], bodyRightTop[1],\
									 outline=outlines, fill=bodyColor)

		
		# triangle
		triangleLeftTop  = [ bodyLeftBottom[0], bodyLeftBottom[1] + triangleOffset ]
		triangleRightTop = [ bodyRightBottom[0], bodyRightBottom[1] + triangleOffset ]
		triangleBottom   = [ (triangleLeftTop[0] + triangleRightTop[0]) / 2, triangleLeftTop[1] + triangleHeight ]

		self.canvas.create_polygon(triangleLeftTop[0], triangleLeftTop[1],\
								   triangleRightTop[0], triangleRightTop[1],\
								   triangleBottom[0], triangleBottom[1],\
								   outline=outlines, fill=triangleColor)


		# left wing
		leftWingRightBottom = bodyLeftBottom
		leftWingLeftBottom  = [ leftWingRightBottom[0] - wingWidth, leftWingRightBottom[1] + wingTransf ]
		leftWingRightTop    = [ bodyLeftBottom[0], bodyLeftBottom[1] - wingHeight ]
		leftWingLeftTop     = [ leftWingRightTop[0] - wingWidth, leftWingRightTop[1] + wingTransf ]

		self.canvas.create_polygon(leftWingRightTop[0], leftWingRightTop[1],\
								   leftWingRightBottom[0], leftWingRightBottom[1],\
								   leftWingLeftBottom[0], leftWingLeftBottom[1],\
								   leftWingLeftTop[0], leftWingLeftTop[1],\
								   outline=outlines, fill=wingColor)


		# right wing
		rightWingRightBottom = bodyRightBottom
		rightWingLeftBottom  = [ rightWingRightBottom[0] + wingWidth, rightWingRightBottom[1] + wingTransf ]
		rightWingRightTop    = [ bodyRightBottom[0], bodyRightBottom[1] - wingHeight ]
		rightWingLeftTop     = [ rightWingRightTop[0] + wingWidth, rightWingRightTop[1] + wingTransf ]

		self.canvas.create_polygon(rightWingRightTop[0], rightWingRightTop[1],\
								   rightWingRightBottom[0], rightWingRightBottom[1],\
								   rightWingLeftBottom[0], rightWingLeftBottom[1],\
								   rightWingLeftTop[0], rightWingLeftTop[1],\
								   outline=outlines, fill=wingColor)

		# window
		windowCenter = [ (bodyLeftBottom[0] + bodyRightBottom[0]) / 2, rightWingRightTop[1] ]
		self.canvas.create_oval(windowCenter[0] - windowSize, windowCenter[1] - windowSize,\
								windowCenter[0] + windowSize, windowCenter[1] + windowSize,\
								outline=outlines, fill=windowColor)


		# head
		headLeftBottom  = bodyLeftTop
		headRightBottom = bodyRightTop
		headTop         = [ (headLeftBottom[0] + headRightBottom[0]) / 2, headLeftBottom[1] - headHeight ]

		self.canvas.create_polygon(headLeftBottom[0], headLeftBottom[1],\
								   headRightBottom[0], headRightBottom[1],\
								   headTop[0], headTop[1],\
								   outline=outlines, fill=headColor)


	def _drawSun(self, pos, \
				 sunColor="yellow", sunSize=50, lightColor="yellow", outlines="black",
				 lightStart=10, lightLength=50,\
				 **kwargs):

		lightR1 = sunSize + lightStart
		lightR2 = lightR1 + lightLength

		self.canvas.create_oval(pos[0] - sunSize, pos[1] - sunSize,\
								pos[0] + sunSize, pos[1] + sunSize,
								outline=outlines, fill=sunColor)

		for angle in self._frange(0, 2 * pi, pi / 150):
			self.canvas.create_line(pos[0] + lightR1 * cos(angle), pos[1] - lightR1 * sin(angle),\
									pos[0] + lightR2 * cos(angle), pos[1] - lightR2 * sin(angle),
									fill=lightColor)

	def _drawTree(self, pos, \
				  color="green", stemColor="brown", outlines="black",\
				  height=100, width=200, stemHeight=100, stemWidth=20, \
				  **kwargs):
		
		stemLeftBottom = pos
		stemRightTop   = [ pos[0] + stemWidth, pos[1] - stemHeight ]
		self.canvas.create_rectangle(stemLeftBottom[0], stemLeftBottom[1],\
									 stemRightTop[0], stemRightTop[1],\
									 outline=outlines, fill=stemColor)
		bodyLeftBottom  = [ pos[0] - (width - stemWidth) / 2 , stemRightTop[1] ]
		bodyRightBottom = [ bodyLeftBottom[0] + width, bodyLeftBottom[1] ]
		bodyTop         = [ pos[0] + stemWidth / 2, bodyLeftBottom[1] - stemHeight ]
		self.canvas.create_polygon(bodyLeftBottom[0], bodyLeftBottom[1],\
								   bodyRightBottom[0], bodyRightBottom[1],\
								   bodyTop[0], bodyTop[1],\
								   outline=outlines, fill=color)

	# --------------------------------------------------------------

	def _initUI(self):
		self.root.title("Have a nice day")
		self.pack(fill=BOTH, expand=1)

		self.windowWidth  = 550
		self.windowHeight = 500

		self.canvas = Canvas(self)

		self._drawLawn()
		self._drawSky()
		self._drawHome([ 30, 350 ])
		self._drawSun([ 400, 100 ])
		self._drawKamakin([ 210, 415 ])
		self._drawRocket([300, 400])

		self._drawTree([ 500, 400 ], height=200, width=60, stemHeight=100)
		self._drawTree([ 40, 450 ], height=50, width=50, stemHeight=34, stemWidth=40,\
					   color="yellow")
		self._drawTree([ 400, 480 ], height=50, width=50, stemHeight=44, stemWidth=10,\
					   color="black")
		self.canvas.pack(fill=BOTH, expand=1)

	def Show(self):
		self.root.geometry(str(self.windowWidth) + "x" + str(self.windowHeight))
		self.root.mainloop()  

def main():
	ex = PictureFrame()
	ex.Show()


if __name__ == '__main__':
	main()