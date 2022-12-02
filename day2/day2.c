#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 8

int decode(char shape) {
    if (shape == 'A' || shape == 'X') {
        return 1;
    }
    if (shape == 'B' || shape == 'Y') {
        return 2;
    }
    if (shape == 'C' || shape == 'Z') {
        return 3;
    }
    return -1;
}

int tally1(int attacker, int defender) {
    int tally = defender - attacker;
    if (tally == 0) {
        return (defender + 3);
    }
    if (tally == 1 || tally == -2){
        return (defender + 6);
    }
    if (tally == -1 || tally == 2){
        return (defender + 0);
    }
    return -1;
}

int tally2(int attacker, int outcome) {
    if (outcome == 1) {
        int defender = attacker - 1 < 1 ? 3 : attacker - 1;
        return (defender + 0);
    }
    if (outcome == 2){
        return (attacker + 3);
    }
    if (outcome == 3){
        int defender = attacker + 1 > 3 ? 1 : attacker + 1;
        return (defender + 6);
    }
    return -1;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == 0) {
        printf("Could not open file. \n");
        return 1;
    }

    char line[LINE_LENGTH];
    int attack;
    int defend_or_outcome;
    int result1 = 0;
    int result2 = 0;

    while (fgets(line, LINE_LENGTH, file)) {
        attack = decode(line[0]);
        defend_or_outcome = decode(line[2]);
        result1 += tally1(attack, defend_or_outcome);
        result2 += tally2(attack, defend_or_outcome);
    }
    printf("Your total score in part 1 is %i.\n", result1);
    printf("Your total score in part 2 is %i.\n", result2);
    fclose(file);
    return 0;
}