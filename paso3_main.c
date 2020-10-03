#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "paso3_wordscounter.h"

#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {
    FILE* input;
    if (argc > 1) {
        char filepath[30];
        memcpy(filepath, argv[1], strlen(argv[1]) + 1);
        input = fopen(filepath, "r");
    } else {
        input = stdin;
    }

    if (! input) {
        return ERROR;
    } else {
        wordscounter_t counter;
        wordscounter_create(&counter);
        wordscounter_process(&counter, input);
        size_t words = wordscounter_get_words(&counter);
        printf("%zu\n", words);
        wordscounter_destroy(&counter);
        return SUCCESS;
    }
}

