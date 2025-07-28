#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 2048

char* read_section(FILE *file, char* contentName);

int is_number(const char* str);

void strip_comments(char* str);

int note_to_midi(const char* note_str);

// was originally a double, but I can't be bothered rn
int midi_to_frequency(int midi); 

// the first element of this array is its size. 
int *parse_notes(char *melody_r);