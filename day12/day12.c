#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 256
#define INT_MAX 2048

void find_best_path(char array[LINE_LENGTH][LINE_LENGTH], int height, int length, int **bestPath, int source[2]) {
    int *visited = (int *) calloc(height * length, sizeof(int));
    int row;
    int col;
    int position;
    for (row=0; row<height; row++) {
        for (col=0; col<length; col++) {
            position = (row * length) + col;
            visited[position] = 0;
            (*bestPath)[position] = INT_MAX;
        }
    }
    position = (source[0] * length) + source[1];
    (*bestPath)[position] = 0;
    int count;
    int c_point[2];
    int n_point[2];
    int cur_dist;
    int new_dist;
    int min_dist;
    for (count=0; count<(height*length); count++) {
        min_dist = INT_MAX;
        for (row=0; row<height; row++) {
            for (col=0; col<length; col++) {
                if(visited[row*length + col] == 0 && (*bestPath)[row*length + col] <= min_dist) {
                    c_point[0]=row;
                    c_point[1]=col;
                    min_dist = (*bestPath)[row*length + col];
                }  
            }
        }
        if (c_point[0] > 0) {
            n_point[0] = c_point[0]-1;
            n_point[1] = c_point[1];
            if (array[n_point[0]][n_point[1]] - array[c_point[0]][c_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
        }
        if (c_point[0] < height-1) {
            n_point[0] = c_point[0]+1;
            n_point[1] = c_point[1];
            if (array[n_point[0]][n_point[1]] - array[c_point[0]][c_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }

        }
        if (c_point[1] > 0) {
            n_point[0] = c_point[0]; 
            n_point[1] = c_point[1]-1;
            if (array[n_point[0]][n_point[1]] - array[c_point[0]][c_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
            
        }
        if (c_point[1] < length-1) {
            n_point[0] = c_point[0];
            n_point[1] = c_point[1]+1;
            if (array[n_point[0]][n_point[1]] - array[c_point[0]][c_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
        }
        visited[c_point[0]*length + c_point[1]] = 1;
    }
    return;
}

void find_best_path_2(char array[LINE_LENGTH][LINE_LENGTH], int height, int length, int **bestPath, int source[2]) {
    int *visited = (int *) calloc(height * length, sizeof(int));
    int row;
    int col;
    int position;
    for (row=0; row<height; row++) {
        for (col=0; col<length; col++) {
            position = (row * length) + col;
            visited[position] = 0;
            (*bestPath)[position] = INT_MAX;
        }
    }
    position = (source[0] * length) + source[1];
    (*bestPath)[position] = 0;
    int count;
    int c_point[2];
    int n_point[2];
    int cur_dist;
    int new_dist;
    int min_dist;
    for (count=0; count<(height*length); count++) {
        min_dist = INT_MAX;
        for (row=0; row<height; row++) {
            for (col=0; col<length; col++) {
                if(visited[row*length + col] == 0 && (*bestPath)[row*length + col] <= min_dist) {
                    c_point[0]=row;
                    c_point[1]=col;
                    min_dist = (*bestPath)[row*length + col];
                }  
            }
        }
        if (c_point[0] > 0) {
            n_point[0] = c_point[0]-1;
            n_point[1] = c_point[1];
            if (array[c_point[0]][c_point[1]] - array[n_point[0]][n_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
        }
        if (c_point[0] < height-1) {
            n_point[0] = c_point[0]+1;
            n_point[1] = c_point[1];
            if (array[c_point[0]][c_point[1]] - array[n_point[0]][n_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }

        }
        if (c_point[1] > 0) {
            n_point[0] = c_point[0]; 
            n_point[1] = c_point[1]-1;
            if (array[c_point[0]][c_point[1]] - array[n_point[0]][n_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
            
        }
        if (c_point[1] < length-1) {
            n_point[0] = c_point[0];
            n_point[1] = c_point[1]+1;
            if (array[c_point[0]][c_point[1]] - array[n_point[0]][n_point[1]] <= 1) {
                new_dist = (*bestPath)[c_point[0]*length + c_point[1]] + 1;
                cur_dist = (*bestPath)[n_point[0]*length + n_point[1]];
                (*bestPath)[n_point[0]*length + n_point[1]] = new_dist<cur_dist ? new_dist : cur_dist;
            }
        }
        visited[c_point[0]*length + c_point[1]] = 1;
    }
    return;
}

int main()
{
    FILE *file;
    int test = 0;
    if (test == 1) {
        file= fopen("test.txt", "r");
    } else {
        file= fopen("input.txt", "r");
    }
    if (file == 0) {
        printf("Could not open file. Testing = %i.\n", test);
        return 1;
    }
    char line[LINE_LENGTH];
    char array[LINE_LENGTH][LINE_LENGTH];
    int length;
    int height;
    int row = 0;
    int col;
    int start[2];
    int end[2];

    while (fgets(line, LINE_LENGTH, file)) {
        length = strlen(line);
        for (col=0; col<length; col++) {
            array[row][col] = line[col];
            if (line[col] == 'S') {
                start[0]=row;
                start[1]=col;
                array[row][col] = 'a';
            }
            if (line[col] == 'E') {
                end[0]=row;
                end[1]=col;
                array[row][col] = 'z';
            }
        }
        row++;
    }
    height = row;
    printf("Read an array of dimensions %ix%i. The start is at (%i,%i) and the end is at (%i,%i). \n", height, length, start[0], start[1], end[0], end[1]);
    //printf("Test: %c.\n",array[height-1][length-1]);

    int *bestPath = (int *) calloc(height * length, sizeof(int));
    find_best_path(array, height, length, &bestPath, start);
    printf("The shortest distance to the destination in Part 1 is %i.\n", bestPath[end[0]*length + end[1]]);

    find_best_path_2(array, height, length, &bestPath, end);
    int winner = INT_MAX;
    for (row=0; row<height; row++) {
        for (col=0; col<length; col++) {
            if(array[row][col] == 'a' && bestPath[row*length + col] <= winner) {
                winner = bestPath[row*length + col];
            }  
        }
    }
    printf("The fewest steps required to move starting from any square with elevation a to the end is %i.\n", winner);
    return 0;
}













