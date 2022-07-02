#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/**
 * Provides helper functions to support hashtable functions.
 *
 * Error detecting memory allocation, prime number generation,
 * getting words and formatting them consistently.
 *
 * @author Jeremy Shanks, Will Johnstone, Matthew Jennings.
 */

/**
 * Error-checking memory allocation. Attempts to allocate
 * memory. If memory allocation fails an error message will be printed to
 * stderr.
 *
 * @param s the size of the thing you wish to allocate memory for.
 */
void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Error-checking memory reallocation. Attempts to reallocate
 * memory. If memory reallocation fails
 * an error message will be printed to stderr.
 *
 * @param p the pointer you wish to reallocate memory for.
 * @param s the size of the thing you wish to reallocate memory for.
 */
void *erealloc(void *p, size_t s){
    void *result = realloc(p, s);
    if (NULL == result){
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Manages the input of words from input STREAM.
 *
 * Example:
 *
 * while (getword(word, sizeof word, stdin) != EOF) {
 *     htable_insert(h, word);
 * }
 *
 * @param s string pointer to put the result in.
 * @param limit max word size.
 * @param stream specified stream for output.
 *
 * @return w - s.
 */
int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    while(!isalnum(c = getc(stream)) && EOF != c)
    ;
    if (EOF == c){
        return EOF;
    } else if (--limit > 0){
        *w++ = tolower(c);
    }
    while(--limit > 0){
        if (isalnum(c = getc(stream))){
            *w++ = tolower(c);
        } else if ('\'' == c){
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
