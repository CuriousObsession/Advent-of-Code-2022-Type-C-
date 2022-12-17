#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#define LINE_LENGTH 512
#define INT_MAX 2048

struct List {
    int length;
    struct List_Cont *first;
};

struct List_Cont {
    int type; // 1 for int, 2 for list
    int num;
    struct List *list;
    struct List_Cont *next;
    struct List *parent;
};

struct Packet {
    int index;
    struct List *left;
    struct List *right;
};

typedef struct List List;
typedef struct List_Cont List_Cont;
typedef struct Packet Packet;


Packet* create_packet(char *left, char *right, int index);
List *create_List(char* str);
List_Cont *create_List_Cont(char* str);
List* int_to_list(int num);
int compare_int(int left, int right);
int compare_List_Cont(List_Cont* left, List_Cont* right);
int compare_List(List*left, List*right);


Packet* create_packet(char *left, char *right, int index) {
    Packet* res = (Packet*) calloc(1, sizeof(Packet));
    res->index = index;
    res->left = create_List(left);
    res->right = create_List(right);
    return res;
}

List *create_List(char* str) {
    List *res = (List*) calloc(1, sizeof(List));
    char* left = strdup(str);
    char* ptr = calloc(1, strlen(str)+1);
    left = left+1;
    int offset;
    int depth;
    int length = 0;
    List_Cont* prev_cont;
    List_Cont* new_cont;

    while(1) {
        memset(ptr, 0, strlen(ptr));
        //printf("left: %s.\n", left);
        if (left[0] == ',') {
            left = left+1;
            continue;
        }
        if (left[0]==']') {
            break;
        }
        if (isdigit(left[0])) {
            offset = 1;
            while(isdigit(left[offset])) {
                offset++;
            }
        }
        if (left[0] == '[') {
            offset = 0;
            depth = 0;
            while(left[offset]) {
                if (left[offset] == '[') {
                    depth++;
                }
                if (left[offset] == ']') {
                    depth--;
                }
                if (left[offset] == ']' && depth == 0) {
                    break;
                }
                offset++;
            }
            offset++;
        }
        memcpy(ptr, left, offset);
        ptr[offset] = '\0';
        //printf("ptr: %s.\n", ptr);

        new_cont = create_List_Cont(ptr);
        new_cont->parent = res;
        if (length == 0) {
            res->first = new_cont;
        } else {
            prev_cont->next = new_cont;
        }
        prev_cont = new_cont;
        length ++;
        left += offset;
    }
    if (length == 0) {
            res->first = NULL;
    }
    res ->length = length;
    return res;
}

List_Cont *create_List_Cont(char* str) {
    char* wrk = strdup(str);
    List_Cont *res = (List_Cont*) calloc(1, sizeof(List_Cont));
    if (wrk[0] == '[') {
        res -> type = 2;
        res -> num = -1;
        res -> list = create_List(wrk);
    } else if (isdigit(wrk[0])){
        res -> type = 1;
        res -> num = atoi(wrk);
        res -> list = NULL;
    } else {
        //printf("Not recognized: \'%s\' and \'%s\'.\n", str, wrk);
        res -> type = -1;
        res -> num = -1;
        res -> list = NULL;
    }
    res -> parent = NULL;
    res -> next = NULL;
    return res;
}

List* int_to_list(int num) {
    List* res = (List*) calloc(1, sizeof(List));
    List_Cont* cont = (List_Cont*) calloc(1, sizeof(List_Cont));
    cont -> type = 1;
    cont -> num = num;
    cont -> list = NULL;
    cont -> next = NULL;
    cont -> parent = res;
    res->length = 1;
    res -> first = cont;
    return res;
}


int compare_int(int left, int right) {
    //printf("Comparing numbers %i and %i.\n", left, right);
    if (left < right) {
        return 1;
    }
    if (left > right) {
        return -1;
    }
    return 0;
}

int compare_List_Cont(List_Cont* left, List_Cont* right) {
    //printf("Comparing %i and %i.\n", left->type, right->type);
    if (left->type == 1 && right->type == 1) {
        return compare_int(left->num, right->num);
    }
    if (left->type == 2 && right->type == 2) {
        return compare_List(left->list, right->list);
    }
    if (left->type == 1 && right->type == 2) {
        return compare_List(int_to_list(left->num), right->list);
    }
    if (left->type == 2 && right->type == 1) {
        return compare_List(left->list, int_to_list(right->num));
    }
    printf("Types not recognized l=%i, r=%i.\n", left->type, right->type);
    return -1;
}

int compare_List(List* left, List* right) {
    int length_l = left->length;
    int length_r = right-> length;
    List_Cont* object_left = left->first;
    List_Cont* object_right = right->first;
    int comparison;
    
    while(1) {
        if(length_l == 0 && length_r > 0) {
            return 1;
        }
        if(length_l > 0 && length_r == 0) {
            return -1;
        }
        if(length_l == 0 && length_r == 0) {
            return 0;
        }
        comparison = compare_List_Cont(object_left, object_right);
        if (comparison != 0) {
            return comparison;
        }
        object_left = object_left -> next;
        object_right = object_right -> next;
        length_l--;
        length_r--;
    }
}



// Quick sort in C
// function to swap elements
void list_swap(List **a, List **b) {
  List* t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int list_partition(List** array, int low, int high) {
  
  // select the rightmost element as pivot
  List* pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (compare_List(array[j], pivot) == 1) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      list_swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  list_swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void list_quickSort(List** array, int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = list_partition(array, low, high);
    
    // recursive call on the left of pivot
    list_quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    list_quickSort(array, pi + 1, high);
  }
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
    size_t bufl = 512;
    size_t bufr = 512;
    char* linel = (char*) calloc(bufl, sizeof(char));
    char* liner = (char*) calloc(bufr, sizeof(char));;
    int index = 1;
    Packet **packets = (Packet**) calloc(256, sizeof(Packet*));

    while (getline(&linel, &bufl, file) != -1) {
        getline(&liner, &bufr, file);
        //printf("Making packet %i with strings %s and %s.\n", index, linel, liner);
        packets[index]= create_packet(linel, liner, index);
        getline(&linel, &bufl, file);
        index ++;
    }
    printf("Created %i packets.\n", index-1);
    int *valid = (int *) calloc(index, sizeof(int));
    int result = 0;

    for (int i=1; i<index; i++) {
        valid[i] = compare_List(packets[i]->left, packets[i]->right);
        if (valid[i] == 1) {
            result += i;
        }
        //printf("Packet %i is %i valid.\n", i, valid[i]);
    }
    printf("The sum of the indices of correct packets is %i.\n", result);

    rewind(file);
    index = 1;
    List **new_packets = (List**) calloc(512, sizeof(List*));
    while (getline(&linel, &bufl, file) != -1) {
        new_packets[index]= create_List(linel);
        index ++;
        getline(&liner, &bufr, file);
        new_packets[index]= create_List(liner);
        index ++;
        getline(&linel, &bufl, file);
    }
    char* key1 = "[[2]]";
    char* key2 = "[[6]]";
    new_packets[index]=create_List(key1);
    List *winner1 = new_packets[index];
    index++;
    new_packets[index]=create_List(key2);
    List *winner2 = new_packets[index];
    int decoder = 1;
    printf("Created %i Lists in part 2.\n", index);
    list_quickSort(new_packets,1,index);
    for (int i=1; i<=index; i++) {
        if (winner1 == new_packets[i]) {
            decoder *= i;
        }
        if (winner2 == new_packets[i]) {
            decoder *= i;
        }
    }
    printf("The decoder key for part 2 is %i.\n", decoder);

    return 0;
}













