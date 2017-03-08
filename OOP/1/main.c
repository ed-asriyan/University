//
// Created by ed on 07.03.17.
//

#include <stdio.h>
#include <stdbool.h>

#include <GL/glut.h>

#include "core/commands.h"
#include "core/execute.h"
#include "core/errors.h"

#include "point.h"

point_t mouse_position = {-1, -1};

bool mouse_button_left_pressed;

bool mouse_button_right_pressed;

void redraw(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.4, 0.2);
	glPointSize(3.0);

	glBegin(GL_LINES);
	command_data_t command_data;
	execute(RENDER, &command_data);

	glEnd();
	glFlush();
}

void mouse_left_handler(int state, int x, int y) {
	switch (state) {
		case GLUT_UP:
			mouse_button_left_pressed = !mouse_button_left_pressed;
			break;
		case GLUT_DOWN:
			break;
		default:
			break;
	}
}

void mouse_right_handler(int state, int x, int y) {
	switch (state) {
		case GLUT_UP:
			mouse_button_right_pressed = !mouse_button_right_pressed;
			break;
		case GLUT_DOWN:
			break;
		default:
			break;
	}
}

void mouse_wheel_handler(int state, int x, int y) {
	const double factor = -0.9;
	command_data_t command_data;
	switch (state) {
		case GLUT_UP:
			command_data.transform_object_data.transformation.type = UNIFORM_SCALING;
			command_data.transform_object_data.transformation.uniform_scaling.factor = factor;
			execute(TRANSFORM_OBJECT, &command_data);
			redraw();
			break;
		case GLUT_DOWN:
			command_data.transform_object_data.transformation.type = UNIFORM_SCALING;
			command_data.transform_object_data.transformation.uniform_scaling.factor = 1.0 / factor;
			execute(TRANSFORM_OBJECT, &command_data);
			redraw();
			break;
		default:
			break;
	}
}

void mouse_button_handler(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			mouse_left_handler(state, x, y);
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_right_handler(state, x, y);
			break;
		case 3:
			if (state != GLUT_UP) {
				mouse_wheel_handler(GLUT_UP, x, y);
			}
			break;
		case 4:
			if (state != GLUT_UP) {
				mouse_wheel_handler(GLUT_DOWN, x, y);
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void mouse_move_handler(int x, int y) {
	if (mouse_position.x >= 0 && mouse_position.y >= 0) {
		int dx = x - mouse_position.x;
		int dy = y - mouse_position.y;

		if (dx || dy) {
			if (mouse_button_left_pressed) {
				command_data_t command_data;
				command_data.transform_object_data.transformation.type = ROTATION;
				command_data.transform_object_data.transformation.rotation.axis_x = -dy;
				command_data.transform_object_data.transformation.rotation.axis_y = dx;
				command_data.transform_object_data.transformation.rotation.axis_z = 0.0;
				command_data.transform_object_data.transformation.rotation.angle = to_radians(1.0);
				execute(TRANSFORM_OBJECT, &command_data);
				redraw();
			} else if (mouse_button_right_pressed) {
				command_data_t command_data;
				command_data.transform_camera_data.transformation.type = TRANSLATION;
				command_data.transform_camera_data.transformation.translation.displacement_x = -dx * 0.01;
				command_data.transform_camera_data.transformation.translation.displacement_y = -dy * 0.01;
				command_data.transform_camera_data.transformation.translation.displacement_z = 0.0;
				execute(TRANSFORM_CAMERA, &command_data);
				redraw();
			}
		}
	}

	mouse_position.x = x;
	mouse_position.y = y;
}

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage:\n");
		printf("\t3dView file_name\n");
		printf("\n");
		printf("Example:\n");
		printf("\t3dView cube.txt\n");
		return -1;
	}

	// glut initialization
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("3D Viewer");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);

	glutDisplayFunc(redraw);

	// subscribe for mouse events
	glutMouseFunc(mouse_button_handler);
	glutPassiveMotionFunc(mouse_move_handler);

	// initialize core
	command_data_t command_data;
	if (execute(STARTUP, &command_data) != NONE) {
		fprintf(stderr, "Can not startup core\n");
		return -10;
	}

	command_data.transform_camera_data.transformation.type = TRANSLATION;
	command_data.transform_camera_data.transformation.translation.displacement_x = 0.0;
	command_data.transform_camera_data.transformation.translation.displacement_y = 0.0;
	command_data.transform_camera_data.transformation.translation.displacement_z = 10.0;
	if (execute(TRANSFORM_CAMERA, &command_data) != NONE) {
		fprintf(stderr, "Can not transform camera\n");
		return -11;
	}

	// load from file
	command_data_t load_command_data;
	load_command_data.load_model_data.file_path = argv[1];
	if (execute(LOAD_MODEL, &load_command_data) != NONE) {
		fprintf(stderr, "Can not load mode from %s\n", load_command_data.load_model_data.file_path);
		return -12;
	}

	glutMainLoop();
}