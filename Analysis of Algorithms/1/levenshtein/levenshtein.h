#ifndef LAB1_LEVENSHTEIN_H
#define LAB1_LEVENSHTEIN_H

#include <stdlib.h>
#include <string.h>

int calc_levenshtein_general(const char* src, const char* dst);

int calc_levenshtein_recoursive(const char* src, const char* dst);

int calc_levenshtein_modified(const char* src, const char* dst);

#endif //LAB1_LEVENSHTEIN_H
