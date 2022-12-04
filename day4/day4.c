#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 128




int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line[LINE_LENGTH];
    char *ptr;
    char delim[] = ",-";
    int low_left;
    int low_right;
    int high_left;
    int hight_right;
    int result1 = 0;
    int result2 = 0;

    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line,delim);
        low_left = atoi(ptr);
        ptr = strtok(NULL, delim);
        high_left = atoi(ptr);
        ptr = strtok(NULL, delim);
        low_right = atoi(ptr);
        ptr = strtok(NULL, delim);
        hight_right = atoi(ptr);
        if (low_left <= low_right && high_left >= hight_right) {
            result1 += 1;
            result2 += 1;

        }
        else if (low_right <= low_left && hight_right >= high_left) {
            result1 += 1;
            result2 += 1;
        }
        else if (low_left <= hight_right && hight_right <= high_left ) {
            result2 += 1;
        }
        else if (low_right <= high_left && high_left <= hight_right) {
            result2 += 1;
        }

    }
    printf("The number of contained pairs is %i.\n", result1);
    printf("The number of intersecting pairs is %i.\n", result2);
    return 0;
    
}