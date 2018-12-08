#include "../headers/read_line.h"

/* Implementation of getline for windows */

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    //If error return

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    //Get first char in file

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }

    //Allocate 128 for the line

    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }

    p = bufptr; //Keep track of the pointer's start

    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {    //If line is bigger than allocate space,
            size = size + 128;             //allocate 128 more bytes
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c; //Take next char

        //If new line break

        if (c == '\n') {
          break;
        }
        c = fgetc(stream);
    }

    //Return the start of the pointer and line's size

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    //Return the number of bytes that have been read

    return p - bufptr - 1;
}
