#include <stdio.h>
#include <stdlib.h>
#include "caesar.h"

/**
 * Reads the distribution of letters in the English alphabet from the specified filename. The file should
 * contain a line with a floating point number for each of the letters representing its frequency
 * @param filename The filename
 * @param distribution an array in which the read data is to be stored
 */
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

void encryption_procedure();

int main(void) {
    char command;

    double reference_distribution[ALPHABET_SIZE];

    read_distribution("distribution.txt", reference_distribution);

    do {
        printf("Caesar Cipher Utility v1\n");
        printf("1. Encrypt a text with the specified shift\n");
        printf("2. Decrypt a text with the specified shift\n");
        printf("3. Compute the frequency distribution of the text\n");
        printf("4. Brute force decryption of a text with a specified distance calculation method\n");
        printf("0. Exit the program\n");
        printf("Please enter an option: \n");

        scanf("%c", &command);
        fgetc(stdin);
        switch (command) {
            case '1':
                encryption_procedure();
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '0':
                printf("Exiting...");
                break;
            default:
                break;
        }

    } while (command != '0');
    return 0;
}
