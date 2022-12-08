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
    int top_position;
    Smart_tree* tree;
    Smart_tree* above;

    while (fgets(line, LINE_LENGTH, file)) {
        for (col=0; col< width; col++) {
            position = (row * width) + col;
            tree_num = line[col] - '0';
            
            top_position = ((row-1) * width) + col;
            above = row == 0 ? NULL : trees[top_position];
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
            tree = trees[position];
            printf("%i,%i\n",position, tree);
        } 
        if (row+1 >= r_capacity) {
            r_capacity = r_capacity * 2;
            Smart_tree** new_trees = (Smart_tree**) realloc(trees, r_capacity * width);
            trees = new_trees;
        }
        row += 1; 
    }

    printf("There are %i visible trees.\n", num_visible);
    int height = row;
    int right_record;
    Smart_tree* below;
    Smart_tree* to_right;
    
    for (row = height-1; row >= 0 ; row--) {
        for (col = width-1; col >= 0; col --) {
            position = (row * width) + col;
            int pos_below = ((row+1) * width) + col;
            int pos_right = (row * width) + col + 1;
            tree = trees[22];
            printf("%i,%i\n",position, tree);
            below = row == (height-1) ? NULL : trees[pos_below];
            to_right = col == (width-1) ? NULL : trees[pos_right];
            if (row == (height-1) || tree->height > below->bot) {
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
    return 0;
}