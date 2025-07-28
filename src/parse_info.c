#include "../include/parse_info.h"

char* read_section(FILE *file, char* contentName) {
    // pain - should probs use snprinft, but whatever
    // it works ¯\_(ツ)_/¯
    // if a buffer overflow happens, you should look here
    char dots3[] = " ---";
    strcat(contentName, dots3);
    
    char start[64] = "--- start ";
    strcat(start, contentName);

    char end[64] = "--- end ";
    strcat(end, contentName);

    char line[MAX_LINE];
    bool in_content = false;
    size_t buffer_size = 1024;
    size_t length = 0;
    char *result = (char *) malloc(buffer_size);
    if (!result) {
        fclose(file);
        return NULL;
    }
    result[0] = '\0';
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, start)) {
            in_content = true;
            continue;
        } else if (strstr(line, end)) {
            in_content = false;
            break;
        }

        if (in_content) {
            size_t line_len = strlen(line);
            if (length + line_len + 1 >= buffer_size) {
                buffer_size *= 2;
                char *new_result = (char *) realloc(result, buffer_size);
                if (!new_result) {
                    free(result);
                    fclose(file);
                    return NULL;
                }
                result = new_result;
            }
            strcat(result, line);
            length += line_len;

        }
    }
    return result; // probs need to free this later~
}

int is_number(const char* str) {
    if (*str == '-') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str++)) return 0;
    }
    return 1;
}

void strip_comments(char* str) {
    char* comment_start = strstr(str, "//");
    if (comment_start != NULL) {
        *comment_start = '\0';  // truncate string at //
    }
}

int note_to_midi(const char* note_str) {
    if (strncmp(note_str, "NOTE_", 5) != 0) return -1;
    
    const char* note = note_str + 5; // skip "NOTE_"
    
    int base = -1;
    int i = 0;
    switch (note[0]) {
        case 'C': base = 0; break;
        case 'D': base = 2; break;
        case 'E': base = 4; break;
        case 'F': base = 5; break;
        case 'G': base = 7; break;
        case 'A': base = 9; break;
        case 'B': base = 11; break;
        default: return -1;
    }

    i = 1;
    if (note[1] == 'S') { // check for sharps
        base += 1;
        i++;
    }

    int octave = atoi(&note[i]);
    int midi = (octave + 1) * 12 + base;

    return midi;
}

int midi_to_frequency(int midi) {
    return 440.0 * pow(2.0, (midi - 69) / 12.0);
}

void add_to_array(int **array, int *size, int *capacity, int value) {
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 10 : (*capacity * 2);
        *array = (int*) realloc(*array, *capacity * sizeof(int));
        if (*array == NULL) {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }
    }
    (*array)[(*size)++] = value;
}

int *parse_notes(char *melody_r) {
    int *result = NULL;
    int count = 0, capacity = 0;
    add_to_array(&result, &count, &capacity, count);
    // remove block comments
    char *start, *end;
    while ((start = strstr(melody_r, "/*")) && (end = strstr(start + 2, "*/"))) {
        end += 2; // move past the "*/"
        memmove(start, end, strlen(end) + 1); // +1 to move the null terminator
    }

    char* line_r = strtok(melody_r, "\n");
    int counter2 = 0;
    while (line_r != NULL) {
        char *token = strtok(line_r, ", ");
        while (token != NULL) {
            // skip the comments
            if (strncmp(token, "//", 2) == 0) {
                break;
            }

            if (is_number(token)) {
                int duration = atoi(token);
                add_to_array(&result, &count, &capacity, duration);
                counter2++;
            } else {
                
                int midi = note_to_midi(token);
                if (midi != -1) {
                    int freq = midi_to_frequency(midi);
                    add_to_array(&result, &count, &capacity, freq);
                    counter2++;
                } else {
                    //printf("Unknown token: %s\n", token);
                    if (strcmp(token, "REST") == 0) {
                        add_to_array(&result, &count, &capacity, 0);
                    }
                }
            }
            token = strtok(NULL, ", ");
        }
        line_r = strtok(NULL, "\n");
    }
    result[0] = count;
    return result;
}