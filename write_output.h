#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX_LINE 1024 // this is also defined in parse_info.h
#define MAXLINE_ 2048

void replace_and_write(const char *line, FILE *outfile, char *target, char* replacement);

// this is an int for debug reasons
int read_and_replace(char *newfilename, char *template_f,  char *tempo, int *lookup_table, int *melody);