//
// Created by lieroz on 04.12.16.
//

/*
 * Module for modifying color of output text.
 */

#ifndef LAB_12_COLORS_H
#define LAB_12_COLORS_H

#define RST        "\033[0m"

#define RED(x)     "\033[31m" x RST
#define GREEN(x)   "\033[32m" x RST
#define YELLOW(x)  "\033[33m" x RST
#define BLUE(x)    "\033[34m" x RST
#define MAGENTA(x) "\033[35m" x RST
#define CYAN(x)    "\033[36m" x RST
#define WHITE(x)   "\033[37m" x RST

#define BOLD(x) "\033[1m" x RST

#define FPRINTF(fmt, ...) fprintf(stdout, fmt "\n", __VA_ARGS__)

#endif //LAB_12_COLORS_H
