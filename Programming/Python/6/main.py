import pygame
import time
from random import randint
from pydrawing import *
from math import sin

SCREEN_WIDTH, SCREEN_HEIGHT = 1280, 720
GROUND_HEIGHT  = 40

BALL_DIAMETER  = 300
BALL_TOP       = SCREEN_HEIGHT - BALL_DIAMETER - GROUND_HEIGHT

SUN_DIAMETER    = 420
SUN_MOVE_CENTER = ( SCREEN_WIDTH / 2 - SUN_DIAMETER / 2, SCREEN_HEIGHT - GROUND_HEIGHT )
SUN_MOVE_RADIUS = SCREEN_WIDTH / 2

MOON_DIAMETER  = 200
MOON_MOVE_CENTER = ( SCREEN_WIDTH / 2 - MOON_DIAMETER / 2, SCREEN_HEIGHT - GROUND_HEIGHT )
MOON_MOVE_RADIUS = SCREEN_WIDTH / 2

pygame.init()

animationScreen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

#objects
ball = Ball(BALL_DIAMETER)
sun  = Sun(SUN_DIAMETER)
moon = Moon(MOON_DIAMETER)

background    = Background(animationScreen, GROUND_HEIGHT)
ball_movement = LoopMovement(animationScreen, ball, 0, BALL_TOP, SCREEN_WIDTH - BALL_DIAMETER, BALL_TOP)
sun_movement  = CircleMovement(animationScreen, sun, SUN_MOVE_CENTER[0], SUN_MOVE_CENTER[1], SUN_MOVE_RADIUS, -3.14)
moon_movement = CircleMovement(animationScreen, moon, MOON_MOVE_CENTER[0], MOON_MOVE_CENTER[1], MOON_MOVE_RADIUS)

done = False
while not done:
	for event in pygame.event.get():
			if event.type == pygame.QUIT:
				done = True

	day_ratio   = sin(moon_movement.angle())
	is_day_time = day_ratio > 0
	if day_ratio < 0:
		day_ratio = 0
	day_ratio = day_ratio ** 1.5

	if day_ratio > 0.9:
		background.shuffle_stars()

	animationScreen.fill((0, 0, 0))

	# redrawing objects
	background.draw_sky(day_ratio)
	ball.draw(not is_day_time)
	sun.draw(day_ratio)
	moon.draw(is_day_time)

	# moving objects
	sun_movement.move(1e-2, )
	moon_movement.move(1e-2, False)
	ball_movement.move(3)

	# drawing ground (exceptional object)
	background.draw_gound()

	display.flip()
	time.wait(1000 // 120)

pygame.quit()