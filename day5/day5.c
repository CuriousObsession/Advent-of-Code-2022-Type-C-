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
        printf("stack_pop error: stack is empty.\n");
        return '_';
    } else {
        char res = (*stack)->val;
        struct stack_node *ptr = *stack;
        *stack = (*stack)->next;
        free(ptr);
        return res;
    }
}

char stack_peek(struct stack_node* stack) {
     if (stack_isEmpty(stack)) {
        printf("stack_peek error: stack is empty.\n");
        return '_';
    } else {
        char res = (stack)->val;
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
    struct stack_node **stacks_2 = malloc(count * sizeof(struct stack_node *));
    char **data = malloc(base * sizeof(char *));
    int i;
    int j;
    char *temp_str;
    char temp_char;
    for (i=0; i < base; i++) {
        fgets(line, LINE_LENGTH, file);
        data[i] = (char *) malloc(LINE_LENGTH+1);
        memset(data[i], 0, LINE_LENGTH+1);
        strcpy(data[i], line);
    }
    for (j=0; j < count; j++) {
        stacks[j] = NULL;
        stacks_2[j] = NULL;
    }
    for (i=0; i < base; i++) {
        for (j=0; j < count; j++) {
            temp_str = data[base-1-i];
            temp_char = temp_str[1 + (j*4) ];
            if (isalpha(temp_char)) {
                if (stack_isEmpty(stacks[j])) {
                    stacks[j] = stack_make(temp_char); 
                    stacks_2[j] = stack_make(temp_char);
                } else {
                    stack_push(temp_char, &stacks[j]);
                    stack_push(temp_char, &stacks_2[j]);
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
    char mover_1;
    char mover_2;
    struct stack_node *temp;
    int k;
    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, move_delim);
        num_move = atoi(ptr);
        ptr = strtok(NULL, move_delim);
        num_from = atoi(ptr);
        ptr = strtok(NULL, move_delim);
        num_to = atoi(ptr);
        for (k=0; k<num_move; k++) {
            mover_1 = stack_pop(&stacks[num_from-1]);
            mover_2 = stack_pop(&stacks_2[num_from-1]);
            if (k == 0) {
                temp = stack_make(mover_2);
            } else {
                stack_push(mover_2, &temp);
            }
            stack_push(mover_1, &stacks[num_to-1]);
        }
        for (k=0; k<num_move; k++) {
            mover_2 = stack_pop(&temp);
            stack_push(mover_2, &stacks_2[num_to-1]);
        }
    }


    // Release everything and end
    char result1[count+1];
    char result2[count+1];
    result1[count]='\0';
    result2[count]='\0';
    for (j=0; j < count; j++) {
        temp = stacks[j];
        result1[j] = stack_peek(temp);
        while (!stack_isEmpty(stacks[j])) {
            stack_pop(&stacks[j]);
        }
        free(stacks[j]);
        temp = stacks_2[j];
        result2[j] = stack_peek(temp);
        while (!stack_isEmpty(stacks_2[j])) {
            stack_pop(&stacks_2[j]);
        }
        free(stacks_2[j]);      
    }
    printf("For part 1, the top crates in each stack spell the code %s. \n", result1);
    printf("For part 2, the top crates in each stack spell the code %s. \n", result2);
    for (i=0; i < base; i++) {
        free(data[i]);
    }
    free(data);
    free(stacks);
    free(stacks_2);
    fclose(file);
    return 0;
}








