//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_TRANSFORMATION_H
#define INC_3DVIEW_TRANSFORMATION_H

typedef enum transformation_type {
	TRANSLATION,
	ROTATION,
	UNIFORM_SCALING,
} transformation_type_t;

typedef struct translation {
	double displacement_x, displacement_y, displacement_z;
} translation_t;

typedef struct rotation {
	double axis_x, axis_y, axis_z;
	double angle;
} rotation_t;

typedef struct uniform_scaling {
	double factor;
} uniform_scaling_t;

typedef struct transformation {
	transformation_type_t type;
	union {
		translation_t translation;
		rotation_t rotation;
		uniform_scaling_t uniform_scaling;
	};
} transformation_t;

#endif //INC_3DVIEW_TRANSFORMATION_H
