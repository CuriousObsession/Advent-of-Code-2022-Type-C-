#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 1024


int x_dif(int head[2], int tail[2]) {
    return (head[0]-tail[0]);
}

int y_dif(int head[2], int tail[2]) {
    return (head[1]-tail[1]);
}

int touching(int head[2], int tail[2]) {
    int x_dif = abs(head[0]-tail[0]);
    int y_dif = abs(head[1]-tail[1]);
    if (x_dif <= 1 && y_dif <= 1) {
        return 1;
    }
    return 0;
}

void move_head(char move, int head[2]) {
    switch (move) {
    case 'U' :
        head[1] = head[1]+1;
        break;
    case 'D' :
        head[1] = head[1]-1;
        break;
    case 'L' :
        head[0] = head[0]-1;
        break;
    case 'R' :
        head[0] = head[0]+1;
        break;
    }
}

void catch_up(int head[2], int tail[2]) {
    if (touching(head, tail)) {
        return;
    } else {
        int x_dif = head[0]-tail[0];
        int y_dif = head[1]-tail[1];
        if ((x_dif + y_dif == 3) || (x_dif + y_dif == 4)) {
            tail[0] = tail[0]+1;
            tail[1] = tail[1]+1;
            return;
        }
        if ((x_dif + y_dif == -3) || (x_dif + y_dif == -4)){
            tail[0] = tail[0]-1;
            tail[1] = tail[1]-1;
            return;
        }
        if (x_dif == 0) {
            if (y_dif == 2) {
                tail[1] = tail[1]+1;
                return;
            }
            if (y_dif == -2) {
                tail[1] = tail[1]-1; 
                return;
            }
        }
        if (y_dif == 0) {
            if (x_dif == 2) {
                tail[0] = tail[0]+1;
                return;
            }
            if (x_dif == -2) {
                tail[0] = tail[0]-1; 
                return;
            }
        }
        if (x_dif == 2 && y_dif == -2) {
            tail[0] = tail[0]+1;
            tail[1] = tail[1]-1;
            return;
        }
        if (x_dif == -2 && y_dif == 2) {
            tail[0] = tail[0]-1;
            tail[1] = tail[1]+1;
            return;
        }
        if ((x_dif == 1 && y_dif == -2) || (x_dif == 2 & y_dif == -1)) {
            tail[0] = tail[0]+1;
            tail[1] = tail[1]-1;
            return;
        }
        if ((y_dif == 1 && x_dif == -2) || (y_dif == 2 & x_dif == -1)) {
            tail[0] = tail[0]-1;
            tail[1] = tail[1]+1;
            return;
        }
        printf("Error: head and tail are not close enough x=%i, y=%i.\n", x_dif, y_dif);
        return;
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
    char *ptr;
    char command;
    int moves;
    char* delim = " ";
    int* board = (int*) calloc(LINE_LENGTH * LINE_LENGTH, sizeof(int));
    int center = LINE_LENGTH / 2;
    int old_head[2];
    int new_head[2];
    int old_tail[2];
    int new_tail[2];
    int i;
    int location;
    int did_it_move;
    for (i=0;i<2;i++) {
        old_head[i]=center;
        old_tail[i]=center;
    }
    board[(center * LINE_LENGTH) + center] = 1;
    int num_visited = 1;
    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, delim);
        command = ptr[0];
        ptr = strtok(NULL, delim);
        moves = atoi(ptr);
        did_it_move = 0;
        for (i=0; i<moves; i++) {

        switch (command) {
        case 'U' :
            new_head[0] = old_head[0];
            new_head[1] = old_head[1] + 1;
            if (!touching(new_head, old_tail)) {
                new_tail[0] = old_head[0];
                new_tail[1] = old_tail[1] + 1;
                did_it_move = 1;
            }
            break;
        case 'D' :
            new_head[0] = old_head[0];
            new_head[1] = old_head[1]-1;
            if (!touching(new_head, old_tail)) {
                new_tail[0] = old_head[0];
                new_tail[1] = old_tail[1]-1;
                did_it_move = 1;
            }
            break;
        case 'L' :
            new_head[0] = old_head[0]-1;
            new_head[1] = old_head[1];
            if (!touching(new_head, old_tail)) {
                new_tail[0] = old_tail[0]-1;
                new_tail[1] = old_head[1];
                did_it_move = 1;
            }
            break;
        case 'R' :
            new_head[0] = old_head[0]+1;
            new_head[1] = old_head[1];
            if (!touching(new_head, old_tail)) {
                new_tail[0] = old_tail[0]+1;
                new_tail[1] = old_head[1];
                did_it_move = 1;
            }
            break;
        }
        if (!did_it_move) {
            new_tail[0] = old_tail[0];
            new_tail[1] = old_tail[1];
        }
        location = (new_tail[0] * LINE_LENGTH) + new_tail[1];
        if (board[location] == 0) {
            board[location] = 1;
            num_visited += 1;
        }
        
        old_head[0]=new_head[0]; 
        old_head[1]=new_head[1];
        old_tail[0]=new_tail[0]; 
        old_tail[1]=new_tail[1]; 
        }   
    }
    printf("At the end of the adventure in Part 1 the tail visited %i squares.\n", num_visited);
    free(board);
    int j;
    int rope[10][2];
    int* board_2 = (int*) calloc(LINE_LENGTH * LINE_LENGTH, sizeof(int));
    rewind(file);
    for (i=0; i<10; i++) {
        for (j=0; j<2; j++) {
            rope[i][j]=center;
        }
    }
    board_2[(center * LINE_LENGTH) + center] = 1;
    int num_9_visited = 1;
    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, delim);
        command = ptr[0];
        ptr = strtok(NULL, delim);
        moves = atoi(ptr);
        did_it_move = 0;
        for (i=0; i<moves; i++) {
            move_head(command, rope[0]);
            for (j=0; j<9; j++) {
                catch_up(rope[j],rope[j+1]);
            }
            location = (rope[9][0] * LINE_LENGTH) + rope[9][1];
            // printf("Head loc: x=%i, y=%i.  Tail 9 loc: x=%i, y=%i.\n", rope[0][0], rope[0][1], rope[9][0], rope[9][1]);
            if (board_2[location] == 0) {
                board_2[location] = 1;
                //printf("visisted position: x=%i, y=%i.\n", rope[9][0], rope[9][1]);
                num_9_visited += 1;
            }      
        }
    }
    printf("At the end of the adventure in Part 2 the 9-tail visited %i squares.\n", num_9_visited);
    return 0;
}






            




