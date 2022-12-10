#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 256

void test_str(int cycle, int regx, int* special_cycle, int* signal, int size) {
    int i;
    for (i=0; i<size; i++) {
        if (special_cycle[i] == cycle) {
            signal[i] = special_cycle[i] * regx;
        }
    }
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }
    char line[LINE_LENGTH];
    char *ret;
    char delim[] = " \n";
    char *ptr;
    char *command;
    int value;
    int regx = 1;

    int cycle = 0;
    int pixel;
    int executing;
    int counter;
    int special_cycle[6] = {20,60,100,140,180,220};
    int signal[6] = {0,0,0,0,0,0};

    char screen[240];
    int crt;

    while(1) {
        //start
        cycle++;
        if (!executing) {
            ret = fgets(line, LINE_LENGTH, file);
            if (ret == NULL) {
                break;
            }
            command = strtok(line, delim);
            if (strcmp(command, "noop") == 0) {
                counter = 1;
                executing = 1;
            } else if (strcmp(command, "addx") == 0) {
                counter = 2;
                ptr = strtok(NULL, delim);
                value = atoi(ptr);
                executing = 1;
            } else {
                printf("Error: unrecognized command %s.\n", command);
                return -1;
            }

        }
        //during
        test_str(cycle, regx, special_cycle, signal, 6);
        pixel = cycle - 1;
        crt = pixel % 40;
        if (pixel <= 240) {
            if (abs(crt-regx) <= 1) {
                screen[pixel] = '#';
            } else {
                screen[pixel] = '.';
            }
        }

        //end
        counter--;
        if (counter == 0) {
            if (strcmp(command, "addx") == 0) {
                regx += value;
            }
            executing = 0;
        }

    }
    int res = 0;
    int i;
    int j;
    for (i=0; i<6; i++) {
        res += signal[i];
    }
    printf("The sum of the signal strengths is %i.\n", res);
    printf("Here is the image on the screen:\n");
    for (i=0; i<6; i++) {
        for (j=0; j<40; j++) {
            printf("%c", screen[(i*40)+j]);
        }
        printf("\n");
    }
    return 0;
}






            




