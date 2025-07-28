#include "../include/parse_info.h"
#include "../include/compress.h"
#include "../include/write_output.h"

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Couldn't open file!");
        return 0;
    }
    char line[MAX_LINE];
    bool in_content = false;

    // get the tempo
    char tempo[] = "tempo";
    char *tempo_number = read_section(file, tempo);

    // get the melody 
    char melody[] = "melody";
    char *melody_r = read_section(file, melody);

    // parse
    int *melody_array = parse_notes(melody_r);
    
    // compress
    int *lookup = make_lookup_table(melody_array);
    // this time compressed
    melody_array = compress_melody(melody_array, lookup);
    
    // write it to an output file
    char filename[] = "./output/output.ino";
    char template_f[] = "./templates/template.ino";
    int return_value = read_and_replace(filename, template_f, tempo_number, lookup, melody_array);
    printf("\nSuccess! File 'output.ino' made/modified in the 'output' folder!\n");
    return return_value;
}