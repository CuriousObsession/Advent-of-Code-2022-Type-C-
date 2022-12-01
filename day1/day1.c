#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 8

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line[LINE_LENGTH];
    int max_calories = 0;
    int max_2 = 0;
    int max_3 = 0;
    int elves[3000];
    int elf_index = 0;
    int curr_elf = 0;
    int value = 0;

    while (fgets(line, LINE_LENGTH, file)) {
        
        if (line[0] == '\n') {
            
            if (curr_elf >= max_calories) {
                max_3 = max_2;
                max_2 = max_calories;
                max_calories = curr_elf;
            } 
            else if (curr_elf >= max_2) {
                max_3 = max_2;
                max_2 = curr_elf;
            }
            else if (curr_elf >= max_3) {
                max_3 = curr_elf;
            }

            elves[elf_index] = curr_elf;
            elf_index++;
            curr_elf = 0;
            continue;
        }

        value = atoi(line);
        curr_elf += value;
    }

    int top_3_calories = max_calories + max_2 + max_3;
    printf("The Elve with the most calories is carrying %i calories.\n", max_calories);
    printf("The top three Elves together carry %i calories.\n", top_3_calories);
    fclose(file);
    return 0;
}