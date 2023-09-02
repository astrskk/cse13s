#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { SIDE = 0, RAZORBACK = 10, TROTTER = 10, SNOUTER = 15, JOWLER = 5 } Position;

const Position pig[7] = {
    SIDE,
    SIDE,
    RAZORBACK,
    TROTTER,
    SNOUTER,
    JOWLER,
    JOWLER,
};

int main(void) {
    int num_players = 2;
    printf("Number of players (2 to 10)? ");
    int scanf_result = scanf("%d", &num_players);

    int scores[num_players];

    for (int i = 0; i < num_players; i++) {
        scores[i] = 0;
    }

    if (scanf_result < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead. \n");
    }

    unsigned seed = 2023;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
    }

    srandom(seed);
    int i = 0;
    int prev = 0;
    int running = 1;
    while (running) {
        if (prev == i) {
            printf("%s\n", player_name[i]);
            prev++;
        }
        int roll = pig[random() % 7];
        scores[i] += roll;

        printf(" rolls %d, has %d\n", roll, scores[i]);

        if (scores[i] >= 100) {
            break;
        }

        if (roll <= 1) {
            i++;
        }

        if (i >= num_players) {
            i = 0;
            prev = 0;
        }
    }

    printf("%s won!\n", player_name[i]);
    return 0;
}
