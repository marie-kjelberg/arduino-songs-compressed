#include "compress.h"

int findElementIndex(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
int count_unique_sorted(int *arr, int size) {
    if (size == 0) return 0;
    
    // make a copy
    int copy[size];
    memcpy(copy, arr, size * sizeof(arr[0]));
    qsort(copy, size, sizeof(int), compare);

    int unique_count = 0;
    bool zero_check = false;
    for (int i = 1; i < size; i++) {
        if (copy[i] == 0) {
            if (zero_check == false) {
                unique_count++;
                zero_check = true;
            }
        }
        if (copy[i] < NOTE_B1 || copy[i] > NOTE_DS8) { continue;}
        
        if (copy[i] != copy[i - 1]) {
            unique_count++;
        }
    }
    return unique_count;
}

int *make_lookup_table(int *melody) {
    int sizeMel = melody[0];
    int unique_elements = count_unique_sorted(melody, sizeMel);

    int *lookup = (int*) malloc((unique_elements) * sizeof(int));
    if (!lookup) {
        return NULL;
    }
    lookup[0] = unique_elements;

    int lastIndex = 1;
    lookup[1] = melody[1];
    for (int i = 1; i < sizeMel; i++) {
        if (lastIndex >= unique_elements) {
            break;
        }
        int target = melody[i];
        if ((target < NOTE_B1 || target > NOTE_D8) && target != 0) {
            continue;
        } 
        int indexFound = findElementIndex(lookup, lookup[0], target);
        if (indexFound == -1) {
            lookup[lastIndex] = target;
            lastIndex++;
        }
    }
    return lookup;
}


int *compress_melody(int *melody, int *lookup_table) {
    // find the number of necesarry notes...
    int sizeMel = melody[0];

    // find the indices  
    // this code is sooo bad lmao
    for (int i = 1; i < sizeMel; i++) {
        int value = melody[i];
        if (value > NOTE_B1) { // less than ~B1, then it is a duration
            // honestly, every 2nd is a duration, but whatever. Fix this whenever~
            melody[i] = findElementIndex(lookup_table, lookup_table[0], value);
        } else {
            // this would be redudant
            //melody[i] = value;
        }
    }

    return melody;
}