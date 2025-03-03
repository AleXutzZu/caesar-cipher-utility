#include <stdio.h>

#define ALPHABET_SIZE 26

/**
 * Reads the distribution of letters in the English alphabet from the specified filename. The file should
 * contain a line with a floating point number for each of the letters representing its frequency
 * @param filename The filename
 * @param distribution an array in which the read data is to be stored
 */
void read_distribution(const char *filename, double distribution[ALPHABET_SIZE]);

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
