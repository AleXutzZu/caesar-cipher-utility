#include <stdio.h>
#include <string.h>
#include "caesar.h"


void encryption_procedure() {
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
    char option;
    while (1) {
        printf("Would you like to enter the text from a file or type it on the keyboard?\n");
        printf("Type 0 for file input\n");
        printf("Type 1 for keyboard input\n");
        scanf("%c", &option);
        fgetc(stdin);
        if (option == '0') {

            printf("Enter the filename you wish to read data from. All data will be read from the first line, at most 1000 characters: \n");
            char filename[80];

            fgets(filename, sizeof filename, stdin);
            unsigned int len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n') filename[len - 1] = '\0';

            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                printf("An unknown error has occurred\n");
                break;
            }

            char buffer[1001];
            fgets(buffer, sizeof buffer, file);

            shift_text(buffer, shift);
            printf("Success! Your encrypted message is: %s\n", buffer);
            break;
        } else if (option == '1') {
            printf("Enter the text on the next line, max. 1000 characters: \n");
            char buffer[1001];
            fgets(buffer, sizeof buffer, stdin);
            shift_text(buffer, shift);
            printf("Success! Your encrypted message is: %s\n", buffer);
            break;
        } else {
            printf("The option is invalid, please try again!\n");
        }
    }

}