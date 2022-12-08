#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 256

typedef struct Smart_tree {
    int height;
    int visible;
    int top;
    int bot;
    int left;
    int right;
} Smart_tree;

Smart_tree* make_tree (int height, int visible, int top, int left, int bot, int right) {
    Smart_tree* res = (Smart_tree*) calloc(1, sizeof(Smart_tree));
    res->height = height;
    res->visible = visible;
    res->top = top;
    res->bot = bot;
    res->left = left;
    res->right = right;
    return res;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }
    char line[LINE_LENGTH];
    
    fgets(line, LINE_LENGTH, file);
    int width = strlen(line)-1;
    int r_capacity = width;
    Smart_tree** trees = (Smart_tree**) calloc(r_capacity * width, sizeof(Smart_tree*));
    rewind(file);

    int num_visible = 0;
    int row = 0;
    int col;
    int tree_num;
    int left_record;
    int top_record;
    int visible;
    int position;
    int pos_above;
    int pos_left;
    Smart_tree* above;
    Smart_tree* to_left;

    while (fgets(line, LINE_LENGTH, file)) {
        for (col=0; col< width; col++) {
            position = (row * width) + col;
            tree_num = line[col] - '0';
            pos_above = ((row-1) * width) + col;
            pos_left = (row * width) + col - 1;
            above = row == 0 ? NULL : trees[pos_above];
            to_left = col == 0 ? NULL : trees[pos_left];
            visible = 0;
            if (row==0 || tree_num > above->top) {
                visible = 1;
                num_visible += 1;
                top_record = tree_num;
            } else {
                top_record = above->top;
            }
            if (col==0 || tree_num > left_record) {
                num_visible = visible == 0 ? num_visible + 1 : num_visible;
                visible = 1;
                left_record = tree_num;
            }
            trees[position] = make_tree(tree_num, visible, top_record, left_record, -1, -1);
        } 
        row += 1; 
    }

    printf("There are %i visible trees.\n", num_visible);
    int height = row;
    Smart_tree* below;
    Smart_tree* to_right;
    Smart_tree* tree;
    int row2;
    
    for (row2 = height-1; row2 >= 0 ; row2--) {
        for (col = width-1; col >= 0; col --) {
            position = (row2 * width) + col;
            int pos_below = ((row2+1) * width) + col;
            int pos_right = (row2 * width) + col + 1;
            tree = trees[position];
            below = row2 == (height-1) ? NULL : trees[pos_below];
            to_right = col == (width-1) ? NULL : trees[pos_right];
            if (row2 == (height-1) || tree->height > below->bot) {
                tree->bot = tree->height;
                if (tree->visible == 0) {
                    num_visible++;
                }
                tree->visible = 1;
            } else {
                tree->bot = below->bot;
            }
            if (col == (width-1) || tree->height > to_right->right) {
                tree->right = tree->height;
                if (tree->visible == 0) {
                    num_visible++;
                }
                tree->visible = 1;
            } else {
                tree->right = to_right->right;
            }
        }
    }
    printf("There are %i visible trees.\n", num_visible);

    int i;
    int winner = 0;
    int tree_score[4];
    int f_score;
    for (row = 0; row<height; row++) {
        for (col = 0; col<width; col++) {
            position = (row * width) + col;
            tree = trees[position];
            for (i=0; i<4; i++) {
                tree_score[i] = 0;
            }
            for (i=col-1; i>= 0; i--) {
                if ((trees[(row * width) + i])->height < tree->height) {
                    tree_score[0]++;
                    continue;
                }
                tree_score[0]++;
                break;
            }
            for (i=col+1; i<width; i++) {
                if ((trees[(row * width) + i])->height < tree->height) {
                    tree_score[1]++;
                    continue;
                }
                tree_score[1]++;
                break;
            }
            for (i=row-1; i>= 0; i--) {
                if ((trees[(i * width) + col])->height < tree->height) {
                    tree_score[2]++;
                    continue;
                }
                tree_score[2]++;
                break;
            }
            for (i=row+1; i<height; i++) {
                if ((trees[(i * width) + col])->height < tree->height) {
                    tree_score[3]++;
                    continue;
                }
                tree_score[3]++;
                break;
            }
            f_score = tree_score[0] * tree_score[1] * tree_score[2] * tree_score[3];
            winner = f_score > winner ? f_score : winner;
        }
    }   
    printf("The highest scenic score possible is %i\n", winner); 
    return 0;
}







