#include <stdio.h>
#include <stdbool.h>
#include "io_functions.h"

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
                run_caesar_known_shift(false);
                break;
            case '2':
                run_caesar_known_shift(true);
                break;
            case '3':
                print_frequencies();
                break;
            case '4':
                run_caesar_brute_force(reference_distribution);
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
