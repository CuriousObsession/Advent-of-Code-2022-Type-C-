#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 128

void slide(char** window, int size, int moves) {
    int j;
    for (j=0; j+moves < size; j++) {
            (*window)[j]= (*window)[j+moves];
    }
}

int check(int count, char** window, int size, char new_char) {
    int i;
    if (count >= size) {
        printf("Error: check -> count is too high");
        return -1;
    }
    if (count == 0) {
        (*window)[0] = new_char;
        return 1;
    }
    for (i=0; i<count; i++) {
        if ((*window)[i] == new_char) {
            slide(window, size, i+1);
            (*window)[count-(i+1)] = new_char;
            return (count-i);
        }
    }
    (*window)[count] = new_char;
    return (count+1);  
}


int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line[LINE_LENGTH];
    int size_1 = 4;
    char *window = (char *) calloc(size_1 + 1, sizeof(char));
    int old_count = 0;
    int new_count = 0;
    int result_1 = 1;
    int keep_going = 1;
    int i;

    while (fgets(line, LINE_LENGTH, file)) {
        for (i=0; i<strlen(line); i++) {
            new_count = check(old_count, &window, size_1, line[i]);
            if (new_count == size_1) {
                result_1 += i;
                keep_going = 0;
                break;
            }
            old_count = new_count;
        }
        if (keep_going) {
            result_1 += strlen(line);
        } else {
            break;
        }
    }
    printf("You need to process %i characters before the first start-of-packet marker.\n", result_1);

    rewind(file);
    int size_2 = 14;
    char *window_2 = (char *) calloc(size_2 + 1, sizeof(char));
    old_count = 0;
    new_count = 0;
    keep_going = 1;
    int result_2 = 1;
    while (fgets(line, LINE_LENGTH, file)) {
        for (i=0; i<strlen(line); i++) {
            new_count = check(old_count, &window_2, size_2, line[i]);
            if (new_count == size_2) {
                result_2 += i;
                keep_going = 0;
                break;
            }
            old_count = new_count;
            printf("%s, %c, %i\n", window_2, line[i], old_count);
        }
        if (keep_going) {
            result_2 += strlen(line);
        } else {
            break;
        }
    }
    printf("You need to process %i characters before the first start-of-message marker.\n", result_2);
    return 0;
}








