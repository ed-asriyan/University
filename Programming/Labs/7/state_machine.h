#ifndef STATEMACHINE_STATE_MACHINE_H
#define STATEMACHINE_STATE_MACHINE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

#define NUMBER_OF_KEYWORDS 38
#define NUMBER_OF_OPERATORS 30

typedef enum {
	ST_USUAL,
	ST_MULTILINE_COMMENT,
	ST_STRING_LITERAL,
	ST_PUNCTUATOR,
	ST_CONSTANT,
	ST_IDENTIFIER,
} state_t;

void read_from_stream(FILE*, FILE*);

#endif //STATEMACHINE_STATE_MACHINE_H
