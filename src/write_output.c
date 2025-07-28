#include "../include/write_output.h"

void replace_and_write(const char *line, FILE *outfile, char *target, char* replacement) {
    const char *pos = line;
    while ((pos = strstr(pos, target)) != NULL) {
        fwrite(line, 1, pos - line, outfile);
        fputs(replacement, outfile);
        line = pos + strlen(target);
        pos = line;
    }
    fputs(line, outfile);
}
int read_and_replace(char *newfilename, char 
    *template_f,  char *tempo, int *lookup_table, int *melody) { // idk
    char tempo_target[] = "{tempo}";
    char lookup_target[] = "{note_table}";
    char melody_target[] = "{compressed_melody}";

    FILE *template_r = fopen(template_f, "r");
    if (!template_r) {
        perror("Error opening template"); return 1;
    }

    FILE *newfile = fopen(newfilename, "w");
    if (!newfile) {
        perror("Error opening newfile"); 
        fclose(newfile); return 1;
    }

    // create the lookup table string
    // each number is max 4 digits. need an additional ", " == two spaces. So 4 * 2 * lookup_table[0]
    size_t lookup_size = 4 * 2 * lookup_table[0];
    char lookup_list[lookup_size]; 
    //lookup_list[0] = '\0'; // init the string
    memset(lookup_list, 0, lookup_size);
    for (size_t i = 1; i < lookup_table[0]; i++) {
        char temp[16];
        sprintf(temp, "%d, ", lookup_table[i]);
        strcat(lookup_list, temp);
    } 

    // create the melody string
    // each number is usually just 2 digits with an optional negative sign. 
    // this + ", " gives 3 * 2 * melody[0]
    size_t melody_size = 3 * 2 * melody[0];
    char melody_str[melody_size];
    memset(melody_str, 0, melody_size);
    for (size_t i = 1; i < melody[0]; i++) {
        char temp[16];
        sprintf(temp, "%d, ", melody[i]);
        strcat(melody_str, temp);
    }

    char line[MAXLINE_];
    char buffer1[MAXLINE_ * 2];
    char buffer2[MAXLINE_ * 2];
    // this is so ugly. There has to be a better way
    while (fgets(line, sizeof(line), template_r)) {
        
        FILE *mem1 = fmemopen(buffer1, sizeof(buffer1), "w+");
        replace_and_write(line, mem1, tempo_target, tempo);
        fflush(mem1);
        rewind(mem1);

        // read result of first replacement
        fgets(buffer1, sizeof(buffer1), mem1);
        fclose(mem1);

        // second replacement
        FILE *mem2 = fmemopen(buffer2, sizeof(buffer2), "w+");
        replace_and_write(buffer1, mem2, lookup_target, lookup_list);
        fflush(mem2);
        rewind(mem2);

        // read result of second replacement
        fgets(buffer2, sizeof(buffer2), mem2);
        fclose(mem2);

        // third replacement final write to the output file
        replace_and_write(buffer2, newfile, melody_target, melody_str);
    }

    fclose(newfile);
    fclose(template_r);
    return 0;
}