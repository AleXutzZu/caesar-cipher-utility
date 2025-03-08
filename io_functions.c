#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "io_functions.h"

void read_distribution(const char *filename, double distribution[ALPHABET_SIZE]) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening file: %s", filename);
        exit(-1);
    }

    char buffer[18];

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        fgets(buffer, sizeof buffer, input);
        if (sscanf(buffer, "%lf", &distribution[i]) != 1) {
            fprintf(stderr, "Error reading floating point number");
            exit(-1);
        }
    }
}

bool read_text(char dest[MAX_SIZE + 1]) {
    char option;
    while (true) {
        printf("Would you like to enter the text from a file or type it on the keyboard?\n");
        printf("Type 0 for file input\n");
        printf("Type 1 for keyboard input\n");
        scanf("%c", &option);
        fgetc(stdin);
        if (option == '0') {

            printf("Enter the filename you wish to read data from. All data will be read from the first line, at most %d characters: \n",
                   MAX_SIZE);
            char filename[80];

            fgets(filename, sizeof filename, stdin);
            unsigned int len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n') filename[len - 1] = '\0';

            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                return false;
            }

            fgets(dest, MAX_SIZE + 1, file);
            break;
        } else if (option == '1') {
            printf("Enter the text on the next line, max. %d characters: \n", MAX_SIZE);

            fgets(dest, MAX_SIZE + 1, stdin);
            break;
        } else {
            printf("The option is invalid, please try again!\n");
        }
    }
    return true;
}

void run_caesar_known_shift(bool reverse_operation) {
    printf("Please input the shift you wish to use (must be a number between 0 and 25, both inclusive): \n");
    int shift;
    int result = scanf("%d", &shift);
    fgetc(stdin);
    if (1 != result) {
        printf("The number is invalid, please try again!\n");
        return;
    }
    if (shift < 0 || shift > 25) {
        printf("The number is invalid, please try again!\n");
        return;
    }

    if (reverse_operation) shift = 26 - shift;

    char text[MAX_SIZE + 1];
    result = read_text(text);

    if (!result) {
        printf("An unknown error has occurred.\n");
        return;
    }

    shift_text(text, shift);
    printf("Success! Your message is: %s\n", text);
}

void print_frequencies() {
    char text[MAX_SIZE + 1];
    bool result = read_text(text);
    if (!result) {
        printf("An unknown error has occurred.\n");
        return;
    }

    double histogram[ALPHABET_SIZE];
    compute_histogram(text, histogram);

    printf("The frequency of each letter is listed below:\n");
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        printf("%c: %lf\n", (char) ('A' + i), histogram[i]);
    }
}

void run_caesar_brute_force(const double reference_distribution[ALPHABET_SIZE]) {
    char text[MAX_SIZE + 1];
    bool result = read_text(text);
    if (!result) {
        printf("An unknown error has occurred\n");
        return;
    }
    char option;

//    fgetc(stdin);

    double top_distances[TOP_N];
    int top_shifts[TOP_N];

    while (true) {
        printf("Please select which distance function you'd like to use:\n");
        printf("Type 0 for Chi-Squared\n");
        printf("Type 1 for Cosine\n");
        printf("Type 2 for Euclidean\n");
        scanf("%c", &option);

        if (option == '0') {
            break_cipher(text, top_shifts, top_distances,
                         reference_distribution, chi_squared_distance);
            break;
        }
        if (option == '1') {
            break_cipher(text, top_shifts, top_distances,
                         reference_distribution, cosine_distance);
            break;
        }
        if (option == '2') {
            break_cipher(text, top_shifts, top_distances,
                         reference_distribution, euclidean_distance);

            break;
        }
        printf("The option is invalid, please try again\n");
    }


}