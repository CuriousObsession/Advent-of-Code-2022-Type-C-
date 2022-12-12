#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 256
#define DIV_ROUND_CLOSEST(n, d) ((((n) < 0) ^ ((d) < 0)) ? (((n) - (d)/2)/(d)) : (((n) + (d)/2)/(d)))

int power(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}

typedef struct Object {
    int worry;
    struct Object* next;
} Object;

typedef struct Monkey {
    int name;
    Object* objects;
    int num_objects;
    char op_type;
    int op_num;
    int div_test;
    int inspected;
    struct Monkey** if_true;
    struct Monkey** if_false;
} Monkey;

Monkey* read_monkey(char* first, FILE* file, Monkey** monkeys) {
    Monkey* res = (Monkey*) calloc(1, sizeof(Monkey));
    char* delim= " \nMSOTI:=aeiounkytrngmspwldvbfh";
    char line[LINE_LENGTH];
    char* ptr;
    char* ptr2;
    ptr = strtok(first, delim);
    res->name = atoi(ptr);
    char* flag;
    
    flag = fgets(line, LINE_LENGTH, file);
    if (!flag) {
        printf("Ran out of lines mid monkey.\n");
        free(res);
        return NULL;
    }
    ptr = strtok(line, delim);
    Object* new_ob;
    Object* old_ob = (Object*) calloc(1, sizeof(Object));
    old_ob->worry = atoi(ptr);
    res->objects = old_ob;
    res->num_objects = 1;
    while(1) {
        ptr = strtok(NULL, delim);
        if (!ptr) {
            break;
        }
        new_ob = (Object*) calloc(1, sizeof(Object));
        new_ob->worry = atoi(ptr);
        old_ob->next = new_ob;
        res->num_objects += 1;
        old_ob = new_ob;
    }

    flag = fgets(line, LINE_LENGTH, file);
    if (!flag) {
        printf("Ran out of lines mid monkey.\n");
        free(res);
        return NULL;
    }
    ptr2 = strtok(line, delim);
    res->op_type = ptr2[0];
    ptr = strtok(NULL, delim);
    if (ptr) {
        res->op_num = atoi(ptr);
    } else {
        if (strcmp(ptr2,"+")==0) {
            res->op_type = '*';
            res->op_num = 2;
        } else {
            res->op_type = '^';
            res->op_num = 2;
        }
    }

    flag = fgets(line, LINE_LENGTH, file);
    if (!flag) {
        printf("Ran out of lines mid monkey.\n");
        free(res);
        return NULL;
    }
    ptr = strtok(line, delim);
    res->div_test = atoi(ptr);

    flag = fgets(line, LINE_LENGTH, file);
    if (!flag) {
        printf("Ran out of lines mid monkey.\n");
        free(res);
        return NULL;
    }
    ptr = strtok(line, delim);
    res->if_true = &(monkeys[atoi(ptr)]);

    flag = fgets(line, LINE_LENGTH, file);
    if (!flag) {
        printf("Ran out of lines mid monkey.\n");
        free(res);
        return NULL;
    }
    ptr = strtok(line, delim);
    res->if_false = &(monkeys[atoi(ptr)]);
    res->inspected = 0;
    return res;
}

void add_object(Object* object, Monkey** mon) {
    Object* c_obj = (*mon) -> objects;
    int num_objects = (*mon) -> num_objects;
    for (int i = 0; i< num_objects; i++) {
        c_obj = c_obj -> next;
    }
    c_obj -> next = object;
    (*mon) -> num_objects ++;
    return;
}

int inspect_item(Monkey** mon) {
    if ((*mon) -> num_objects == 0) {
        return -1;
    }
    Object* c_obj = (*mon) -> objects;
    Object* n_obj = c_obj -> next;
    (*mon) -> num_objects --;
    (*mon) -> inspected ++;
    (*mon) -> objects = n_obj;
    int worry = c_obj -> worry;
    printf("%i\n",worry);
    char type = (*mon) -> op_type;
    if (type == '+') {
        worry += ((*mon) -> op_num);
    } else if (type == '*') {
        worry *= ((*mon) -> op_num);
    } else if (type == '^') {
        worry = power(worry,((*mon) -> op_num));
    }
    worry = DIV_ROUND_CLOSEST(worry, 3);
    c_obj -> worry = worry;
    if (worry % ((*mon)->div_test) == 0) {
        add_object(c_obj, (*mon)->if_true);
    } else {
        add_object(c_obj, (*mon)->if_true);
    }  
    return 0;
}

int main()
{
    FILE *file;
    int test = 1;
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
    int num_monkeys = 0;
    Monkey** monkeys = (Monkey **) calloc(64, sizeof(Monkey*));
    Monkey* c_monkey;

    while (fgets(line, LINE_LENGTH, file)) {
        printf("%s", line);
        monkeys[num_monkeys] = read_monkey(line, file, monkeys);
        num_monkeys ++;
        fgets(line, LINE_LENGTH, file);
    }
    printf("Read %i monkeys.\n", num_monkeys);

    int rounds = 1;
    int items;
    int i;
    int j;
    int k;
    for (i=0; i<rounds; i++) {
        for(j=0; j<num_monkeys; j++) {
            c_monkey = monkeys[j];
            items = c_monkey->num_objects;
            for(k=0;k<items;k++) {
                inspect_item(&c_monkey);
            }
        }
    }

    c_monkey = monkeys[1];
    printf("%i.\n", (c_monkey->objects)->worry);
    return 0;
}






            




