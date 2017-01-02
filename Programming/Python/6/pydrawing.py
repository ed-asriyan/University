from pygame import *
from math import sin, cos, pi
from random import randint

def frange(begin, end, step):
	while begin <= end:
		yield begin
		begin += step


class Movement:
	def __init__(self, screen, surface, x_pos, y_pos):
		self._screen     = screen
		self._surface    = surface
		self._curr_angle = 0
		self._x_pos      = x_pos
		self._y_pos      = y_pos

	def _rot_center(self, angle):
		"""rotate an image while keeping its center and size"""
		image = self._surface

		orig_rect = image.get_rect()
		rot_image = transform.rotate(image, angle)
		rot_rect = orig_rect.copy()
		rot_rect.center = rot_image.get_rect().center
		rot_image = rot_image.subsurface(rot_rect).copy()
		
		return rot_image

	def angle(self, val=None):
		if not val is None:
			self._curr_angle = int(val)
		return self._curr_angle

	def surface(self, val=None):
		if not val is None:
			self._surface = val
		return self._surface

	def x_pos(self, val=None):
		if not val is None:
			self._x_pos = int(val)
		return self._x_pos

	def y_pos(self, val=None):
		if not val is None:
			self._y_pos = int(val)
		return self._y_pos

	def move(self, dx, dy, with_rotation=True, forward_direction=True):
		self._curr_angle += (180 * (dx ** 2 + dy ** 2) ** 0.5 / max(self._surface.get_width(), self._surface.get_height())) * (1 if forward_direction else -1)
		self._x_pos      += dx
		self._y_pos      += dy

		new_ball = self._rot_center(self._curr_angle) if with_rotation else self._surface

		self._screen.blit(new_ball, (self._x_pos, self._y_pos))

class LoopMovement(Movement):
	def __init__(self, screen, surface, begin_x, begin_y, end_x, end_y):
		Movement.__init__(self, screen, surface, begin_x, begin_y)

		self._begin_x = begin_x
		self._begin_y = begin_y
		self._end_x   = end_x
		self._end_y   = end_y

		self._x_length    = begin_x - end_x
		self._y_length    = begin_y - end_y
		self._path_length = (self._x_length ** 2 + self._y_length ** 2) ** 0.5

		self._is_forward_direction = True
		
		self._x_step = (self._x_length / self._path_length) * (1 if end_y - begin_y else -1)
		self._y_step = (self._y_length / self._path_length) * (1 if end_y - begin_y else -1)

		self._y_direction = 1 if end_y - begin_y else -1

	def move(self, d, with_rotation=True):

		b_x = min(self._begin_x, self._end_x)
		e_x = max(self._end_x,   self._end_x)
		b_y = min(self._begin_y, self._end_y)
		e_y = max(self._end_y,   self._end_y)

		if not (b_x <= self._x_pos <= e_x) or not (b_y <= self._y_pos <= e_y):
			self._is_forward_direction = not self._is_forward_direction

		d = abs(d) if self._is_forward_direction else -abs(d)

		Movement.move(self, d * self._x_step, d * self._y_step, with_rotation, not self._is_forward_direction)

class CircleMovement(Movement):
	def __init__(self, screen, surface, x_center, y_center, radius, angle=0):
		Movement.__init__(self, screen, surface, x_center - radius, y_center)

		self._curr_circle_angle = angle
		self._center_x = x_center
		self._center_y = y_center
		self._radius   = radius

	def move(self, angle, with_rotation=True, forward_direction=True):
		self._curr_circle_angle += angle

		new_x = self._center_x - self._radius * cos(self._curr_circle_angle)
		new_y = self._center_y + self._radius * sin(self._curr_circle_angle)

		Movement.move(self, new_x - self._x_pos, new_y - self._y_pos, with_rotation, forward_direction)

	def center(self, x_pos=None, y_pos=None):
		if not (x_pos is None) and not (y_pos is None):
			self._center_x = self._x_pos
			self._center_y = self._y_pos
		return self._center_x, self._center_y

	def angle(self, val=None):
		if not val is None:
			self._curr_circle_angle = float(val)

		return self._curr_circle_angle

# objects
class Ball(Surface):
	def __init__(self, diameter):
		Surface.__init__(self, (diameter, diameter), SRCALPHA)
		self._diameter = diameter 
		self.draw()

	def draw(self, happy=False):
		diameter = self._diameter

		# body
		draw.circle(self, (0, 0, 0), [ diameter // 2 ] * 2, diameter // 2)
		draw.circle(self, (249,195,100), [ diameter // 2] * 2, diameter // 2 - diameter // 90)

		# eyes
		draw.circle(self, (255, 255, 50),  [ diameter // 4 ] * 2,                       diameter // 10)
		draw.circle(self, (255, 255, 50),  [ diameter - diameter // 4, diameter // 4 ], diameter // 10)

		# nose
		draw.circle(self, (255, 100, 0), [ diameter // 2, diameter // 2 ], diameter // 20)

		# mouse
		if happy:
			draw.arc(self, (255, 0, 0), (diameter // 4, diameter // 4, diameter // 2, diameter // 2), 5*pi/4, 7*pi/4, 6)
		else:
			draw.arc(self, (255, 0, 0), (diameter // 4, 3*diameter // 4, diameter // 2, diameter // 2), pi/4, 3*pi/4, 6)

class Sun(Surface):
	def __init__(self, diameter):
		Surface.__init__(self, (diameter, diameter), SRCALPHA)
		self._diameter = diameter 
		# self.draw()

	def draw(self, day_ratio):
		self.fill((0, 0, 0, 0))
		self.set_alpha(255)

		sun_diameter = int(self._diameter / 2 * 0.4)
		rays_begin   = int(self._diameter / 2 * 0.5)
		rays_end     = int(rays_begin + (self._diameter / 2 - rays_begin) * day_ratio)

		center = self._diameter // 2

		# body
		draw.circle(self, (0, 0, 0), [ center ] * 2, sun_diameter)
		draw.circle(self, (255, 255, 0), [ center ] * 2, sun_diameter - sun_diameter // 90)

		for ray_angle in frange(0, 2 * pi, pi / 10):
			draw.line(self, (255, 255, 0), ( center + rays_begin * cos(ray_angle), center - rays_begin * sin(ray_angle)), ( center + rays_end * cos(ray_angle), center - rays_end * sin(ray_angle) ) )

class Moon(Surface):
	def __init__(self, diameter):
		Surface.__init__(self, (diameter, diameter), SRCALPHA)
		self._diameter = diameter 
		self.draw()

	def draw(self, happy=False):
		diameter = self._diameter

		# body
		draw.circle(self, (0, 0, 0), [ diameter // 2 ] * 2, diameter // 2)
		draw.circle(self, (193, 193, 193), [ diameter // 2] * 2, diameter // 2 - diameter // 90)

class Background:
	def __init__(self, screen, ground_height):
		self._screen = screen
		self._ground_height = int(ground_height)

		self._screen_width, self._screen_height = height = self._screen.get_size()

		self.shuffle_stars()

	def shuffle_stars(self):
		stars_count = int(self._screen_height * self._screen_height * 1e-3)
		self._stars = [ ( randint(0, int(self._screen_width)), randint(0, int(self._screen_height - self._ground_height)), randint(0, 3) ) for i in range(stars_count) ]

	def draw_gound(self):
		draw.rect(self._screen, (0, 255, 0), (0, self._screen_height, self._screen_width, -self._ground_height))

	def draw_sky(self, day_ratio):
		draw.rect(self._screen, ( 70 * day_ratio, 100 * day_ratio, 255 * day_ratio ), ( 0, 0, self._screen_width, self._screen_height - self._ground_height ))
		# draw.rect(self._screen, (70 * is_day_time, 100 * is_day_time, 255 if is_day_time else 50), (0, 0, self._screen_width, self._screen_height - self._ground_height))

		star_ratio = (0.2 - day_ratio) * 5
		if star_ratio < 0:
			star_ratio = 0

		if star_ratio:
			for star in self._stars:
				surf = Surface(( star[2], star[2] ), SRCALPHA)
				draw.circle(surf, (255, 255, 255, star_ratio * 255), (star[2] // 2, star[2] // 2), star[2] // 3)
				self._screen.blit(surf, (star[0], star[1]))
