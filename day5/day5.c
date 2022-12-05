#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 128


struct stack_node{
    char val;
    struct stack_node *next;
};

struct stack_node* stack_make(char val) {
    struct stack_node *res = (struct stack_node*) malloc(sizeof(struct stack_node));
    res->val = val;
    res->next = NULL;
    return res;
}

char stack_isEmpty(struct stack_node* stack) {
    if (stack == NULL) {
        return 1;
    }
    return 0;
}

void stack_push(char val, struct stack_node** stack) {
    struct stack_node *new = stack_make(val);
    if (stack_isEmpty(*stack)) {
        *stack = new;
    } else {
        new->next = *stack;
        *stack = new;
    }
}

char stack_pop(struct stack_node** stack) {
    if (stack_isEmpty(*stack)) {
        printf("stack_pop errorr: stack is empty.\n");
        return -1;
    } else {
        char res = (*stack)->val;
        struct stack_node *ptr = *stack;
        *stack = (*stack)->next;
        free(ptr);
        return res;
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
    int result1 = 0;
    int result2 = 0;
    char delim[] = " []";
    char *ptr;

    // Find where the stacks end and how many there are
    int base = 0;
    int count = 0;
    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, delim);
        if (isalpha(ptr[0])) {
            base++;
            continue;
        } else if (isdigit(ptr[0])){
            count = 1;
            while (strtok(NULL,delim)) {
                count++;
            }
            break;
        } else {
            printf("Error: Input text does not start with stacks.\n");
        }
    }

    //Make the stacks
    rewind(file);
    struct stack_node **stacks = malloc(count * sizeof(struct stack_node *));
    char **data = malloc(base * sizeof(char *));
    int i;
    int j;
    for (i=0; i < base; i++) {
        fgets(line, LINE_LENGTH, file);
        data[i] = (char *) malloc(LINE_LENGTH+1);
        strcpy(data[i], line);
        printf("%c", data[i][1]);
    }
    for (j=0; j < count; j++) {
        stacks[j] = NULL;
    }
    for (i=0; i < base; i++) {
        for (j=0; j < count; j++) {
            if (isalpha(data[base-1-i][1 + (j*4) ])) {
                if (stack_isEmpty(stacks[j])) {
                    stacks[j] = stack_make(data[base-1-i][1+(j*4)]); 
                    //printf("%c", stacks[j]->val);
                } else {
                    stack_push(data[base-1-i][1+(j*4)], &stacks[j]);
                }
                
            }

        }

    }
    fgets(line, LINE_LENGTH, file);
    fgets(line, LINE_LENGTH, file);

    //Move the stacks
    char move_delim[]= " []movefrt";
    int num_move;
    int num_from;
    int num_to;
    char mover;
    int k;
    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, move_delim);
        num_move = atoi(ptr);
        ptr = strtok(NULL, move_delim);
        num_from = atoi(ptr);
        ptr = strtok(NULL, move_delim);
        num_to = atoi(ptr);
        for (k=0; k<num_move; k++) {
            mover = stack_pop(&stacks[num_from-1]);
            stack_push(mover, &stacks[num_to-1]);
        }
    }


    // Release everything and end
    for (j=0; j < count; j++) {
        printf("%c", stacks[j]->val);
        free(stacks[j]);
    }
    for (i=0; i < base; i++) {
        free(data[i]);
    }
    free(data);
    free(stacks);
    fclose(file);
    return 0;
}








