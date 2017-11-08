//
// Created by ed on 08.11.17.
//

#include <stdio.h>
#include <time.h>

#include "levenshtein/levenshtein.h"

#define BUFFER_SIZE 128

typedef struct TestResult {
    clock_t general;
    clock_t modified;
    clock_t recoursive;
    unsigned int test_number;
};

clock_t test_general(unsigned int tests_number, const char* src, const char* dst) {
    clock_t result = 0;
    for (unsigned int i = 0; i < tests_number; ++i ) {
        clock_t start_time = clock();
        calc_levenshtein_general(src, dst);
        result += clock() - start_time;
    }
    return result;
}

clock_t test_recoursive(unsigned int tests_number, const char* src, const char* dst) {
    clock_t result = 0;
    for (unsigned int i = 0; i < tests_number; ++i ) {
        clock_t start_time = clock();
        calc_levenshtein_recoursive(src, dst);
        result += clock() - start_time;
    }
    return result;
}

clock_t test_modified(unsigned int tests_number, const char* src, const char* dst) {
    clock_t result = 0;
    for (unsigned int i = 0; i < tests_number; ++i ) {
        clock_t start_time = clock();
        calc_levenshtein_modified(src, dst);
        result += clock() - start_time;
    }
    return result;
}


void generate_string(char* str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        str[i] = (char) (rand() % 128);
    }
    str[len] = '\0';
}

int main() {
    srand((unsigned int) time(NULL));

    unsigned int len_min;
    printf("Enter min length: ");
    scanf("%u", &len_min);

    unsigned int len_max;
    printf("Enter max length: ");
    scanf("%u", &len_max);

    unsigned int len_step;
    printf("Enter step      : ");
    scanf("%u", &len_step);

    unsigned int tests_number;
    printf("Enter tests number: ");
    scanf("%u", &tests_number);


    printf("| Length | Distance | Recoursive | General | Modified |\n");
    printf("|--------|----------|------------|---------|----------|\n");
    for (unsigned int i = len_min; i <= len_max; i += len_step) {
        char* const src = (char*)malloc(sizeof(char) * (i + 1));
        char* const dst = (char*)malloc(sizeof(char) * (i + 1));

        generate_string(src, i);
        generate_string(dst, i);

        clock_t general = test_general(tests_number, src, dst);
        clock_t modified = test_modified(tests_number, src, dst);
        clock_t recoursive = test_recoursive(tests_number, src, dst);
        int distance = calc_levenshtein_modified(src, dst);

        double general_ps = (double)general / tests_number;
        double modified_ps = (double)modified / tests_number;
        double recoursive_ps = (double)recoursive / tests_number;

        printf("| %6u | %8u | %10.2lf | %7.2lf | %8.2lf |\n", i, distance, recoursive_ps, general_ps, modified_ps);

        free(dst);
        free(src);
    }

    return 0;
}
