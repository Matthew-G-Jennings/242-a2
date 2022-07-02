#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Defines helper functions to support tree ADT functions.
 *
 * Error detecting memory allocation, reallocation, getting
 * words and formatting them consistently.
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
extern void *emalloc(size_t);

/**
 * Error-checking memory reallocation. Attempts to reallocate
 * memory. If memory reallocation fails
 * an error message will be printed to stderr.
 *
 * @param p the pointer you wish to reallocate memory for.
 * @param s the size of the thing you wish to reallocate memory for.
 */
extern void *erealloc(void *, size_t);

/**
 * Manages the input of words from input STREAM. ?
 *
 * Example:
 *
 * while (getword(word, sizeof word, stdin) != EOF) {
 *     htable_insert(h, word);
 * }
 *
 * @param s A string pointer to put the result in.
 * @param limit max word size.
 * @param stream specified stream for output.
 *
 * @return w - s.
 */
extern int getword(char *s, int limit, FILE *stream);

#endif
