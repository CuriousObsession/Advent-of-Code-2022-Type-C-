#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 128

int priority(char item) {
    if (islower(item)) {
        return (item-96);
    }
    if (isupper(item)) {
        return (item-38);
    }
    return -10000000;
}



int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line[LINE_LENGTH];
    size_t compartment_length = 0;
    int result1 = 0;

    int i = 0; 
    int j = 0; 
    int k = 0;
    int keep_going = 1;
    while (fgets(line, LINE_LENGTH, file)) {
        compartment_length = (strlen(line)-1)/2;
        
        for (i=0; i<compartment_length && keep_going; i++) {
            for (j=0; j<compartment_length && keep_going; j++) {
                if (line[i] == line[compartment_length+j]) {
                    result1 += priority(line[i]);
                    keep_going = 0;
                }
            }
        }
        keep_going = 1;
    }
    printf("The sum of the priorities of the copied items in part 1 is %i.\n", result1);
    fclose(file);

    file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line2[LINE_LENGTH];
    char line3[LINE_LENGTH];
    int result2 = 0;
    keep_going = 1;

    while (fgets(line, LINE_LENGTH, file)) {
        fgets(line2, LINE_LENGTH, file);
        fgets(line3, LINE_LENGTH, file);
        for (i=0; i < (strlen(line)-1) && keep_going; i++) {
            for (j=0; j < (strlen(line2)-1) && keep_going; j++) {
                for (k=0; k < (strlen(line3)-1) && keep_going; k++) {
                    if (line[i]==line2[j] && line[i]==line3[k]) {
                        result2 += priority(line[i]);
                        keep_going = 0;
                    }
                }
            }
        }
        keep_going = 1;
    }

    printf("The sum of the priorities of the badges in part 2 is %i.\n", result2);
    fclose(file);
    return 0;
}