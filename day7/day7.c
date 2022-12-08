#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 128
#define SUBDIR_LENGTH 64
#define VALID 100000
#define TOTAL 70000000
#define UPDATE 30000000

struct dir {
    char *name;
    int size;
    int total_size;
    int valid_size;
    int num_children;
    int child_capacity;
    struct dir *parent;
    struct dir **subdirs; 
};

int is_numeric(char* str) {
    int length = strlen(str);
    int i;
    for (i = 0; i < length; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

struct dir* dir_make(char *name, struct dir *parent) {
    struct dir* res = (struct dir*) calloc(1, sizeof(struct dir));
    char *res_name = strdup(name);
    res->name = res_name;
    res->size = 0;
    res->total_size = 0;
    res->valid_size = 0;
    res->parent = parent;
    struct dir **new_subdirs = (struct dir **) calloc(SUBDIR_LENGTH, sizeof(struct dir*));
    res ->subdirs = new_subdirs;
    res->num_children = 0;
    res->child_capacity = SUBDIR_LENGTH;
    return res;
}

void dir_add_size(struct dir** directory, int edit) {
    (*directory)->size += edit;
}

void dir_add_child(struct dir** directory, struct dir** child) {
    int children = (*directory)->num_children;
    int capacity = (*directory)->child_capacity;
    if (children >= capacity) {
        struct dir **new_subdirs = (struct dir **) realloc((*directory)->subdirs, (*directory)->child_capacity + SUBDIR_LENGTH);
        (*directory)->subdirs = new_subdirs;
        (*directory)->child_capacity = capacity + SUBDIR_LENGTH;
    }
    ((*directory)->subdirs)[children] = *child;
    (*child)->parent = *directory;
    (*directory)->num_children = children + 1;
    return;
}

int dir_is_child(struct dir* directory, char* child) {
    int i;
    struct dir* cur_child;
    for (i=0; i< directory->num_children; i++) {
        cur_child = (directory->subdirs)[i];
        if (!strcmp(cur_child->name,child)) {
            return 1;
        }
    }
    return 0;
}

int dir_move_to_child(struct dir** directory, char* child) {
    int i;
    struct dir* cur_child;
    for (i=0; i< (*directory)->num_children; i++) {
        cur_child = ((*directory)->subdirs)[i];
        if (!strcmp(cur_child->name,child)) {
            *directory = cur_child;
            return 1;
        }
    }
    return 0;
}

void dir_compute_valid_size(struct dir** directory) {
    int i;
    struct dir* cur_child;
    int valid_size = 0;
    (*directory)->total_size = (*directory)->size;

    for (i=0; i< (*directory)->num_children; i++) {
        cur_child = ((*directory)->subdirs)[i];
        dir_compute_valid_size(&cur_child);
        (*directory)->total_size += cur_child->total_size;
        valid_size += cur_child->valid_size;
    }
    if ((*directory)->total_size <= VALID) {
        (*directory)->valid_size = (*directory)->total_size + valid_size;
    } else {
        (*directory)->valid_size = valid_size;
    }
}

void dir_compute_winner(struct dir** directory, struct dir** winner, int goal) {
    int i;
    struct dir* cur_child;
    for (i=0; i< (*directory)->num_children; i++) {
        cur_child = ((*directory)->subdirs)[i];
        dir_compute_winner(&cur_child, winner, goal);
        if (cur_child->total_size >= goal) {
            if (*winner) {
                if (cur_child->total_size >= (*winner)->total_size) {
                    continue;
                }
            }
            (*winner) = cur_child;
        }
    }
    if ((*directory)->total_size >= goal && !(*winner)) {
        (*winner) = (*directory);
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
    char delim[] = " \n";
    char *ptr;
    char *name;
    char *size;
    char *command;
    char *new_dir;
    struct dir *top_dir = dir_make("/", NULL);
    struct dir *current_dir = top_dir;
    int are_listing = 0;
    int flag;

    while (fgets(line, LINE_LENGTH, file)) {
        ptr = strtok(line, delim);
        
        if (!strcmp(ptr,"$")){
            are_listing = 0;
            command = strtok(NULL, delim);
            
            if (!strcmp(command,"ls")) {
                are_listing = 1;
            
            } else if (!strcmp(command,"cd")) {
                new_dir = strtok(NULL, delim);
                
                if (!strcmp(new_dir,"/")) {
                    current_dir = top_dir;
                
                } else if (!strcmp(new_dir,"..")) {
                    if (current_dir->parent) {
                        current_dir = current_dir->parent;
                    } else {
                        current_dir = top_dir;
                    }
                
                } else {
                    flag = dir_move_to_child(&current_dir, new_dir);
                    if (flag == 0) {                    
                        printf("Error: Directory %s is not a child of %s. Disregard and continue.\n", new_dir, current_dir->name);
                    }
                }
            
            } else {
                printf("Error: Command %s not recognized.\n", command);
                return 1;
            }

        } else if (are_listing && !strcmp(ptr,"dir")) {
            name = strtok(NULL, delim);
            if (!dir_is_child(current_dir,name)) {
                struct dir* new_dir = dir_make(name, current_dir);
                dir_add_child(&current_dir, &new_dir);
            }

        } else if (are_listing && is_numeric(ptr)) {
            dir_add_size(&current_dir, atoi(ptr));

        } else {
            printf("Error: Input text is not appropriately formatted: first token in line is %s and listing is %i.\n", ptr, are_listing);
            return 1;
        }
        //printf("%s, %i, %s, %i, %i\n", line, are_listing, current_dir->name, current_dir->size, current_dir->num_children);
    }

    dir_compute_valid_size(&top_dir);
    printf("The sum of the total sizes of directories of small size is %i.\n", top_dir->valid_size);
    int goal = top_dir->total_size + UPDATE - TOTAL;
    struct dir* winner = NULL;
    dir_compute_winner(&top_dir, &winner, goal);
    if (winner) {
        printf("The total size of the smallest big enough directory is %i and the goal is %i.\n", winner->total_size, goal);
    }
    return 0;
}








