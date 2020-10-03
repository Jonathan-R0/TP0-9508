#include "paso2_wordscounter.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define STATE_WAITING_WORD 0
#define STATE_IN_WORD 1
#define STATE_FINISHED 2

// Compara el caracter leído c y define el nuevo estado.
static char wordscounter_next_state(wordscounter_t *self, char state, char c);

void wordscounter_create(wordscounter_t *self) {
    self->words = 0;
}

size_t wordscounter_get_words(wordscounter_t *self) {
    return self->words;
}

void wordscounter_process(wordscounter_t *self, FILE *text_file) {
    char state = STATE_WAITING_WORD;
    do {
        int c = getc(text_file);
        state = wordscounter_next_state(self, state, c);
    } while (state != STATE_FINISHED);
}

static char wordscounter_next_state(wordscounter_t *self, char state, char c) {
    char* delim_words = malloc(7 * sizeof(char));
    delim_words[0] = ' ';
    delim_words[1] = ',';
    delim_words[2] = '.';
    delim_words[3] = ';';
    delim_words[4] = ':';
    delim_words[5] = '\n';
    delim_words[6] = '\0';

    char next_state = state;
    if (c == EOF) {
        next_state = STATE_FINISHED;
    } else if (state == STATE_WAITING_WORD) {
        if (strchr(delim_words, c) == NULL)
            next_state = STATE_IN_WORD;
    } else if (state == STATE_IN_WORD) {
        if (strchr(delim_words, c) != NULL) {
            self->words++;
            next_state = STATE_WAITING_WORD;
        }
    }
    return next_state;
}

