#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_N 3

/**
 * Reads the distribution of letters in the English alphabet from the specified filename. The file should
 * contain a line with a floating point number for each of the letters representing its frequency
 * @param filename The filename
 * @param distribution an array in which the read data is to be stored
 */
void read_distribution(const char *filename, double distribution[ALPHABET_SIZE]) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        exit(-1);
    }

    char buffer[18];

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        fgets(buffer, sizeof buffer, input);
        if (sscanf(buffer, "%lf", &distribution[i]) != 1) {
            exit(-1);
        }
    }
}

/**
 * Computes the frequency array of the given text
 * @param text the text to analyze
 * @param histogram the array in which to store the data
 */
void compute_histogram(const char *text, double histogram[ALPHABET_SIZE]) {
    for (unsigned int i = 0; text[i] != '\0'; ++i) {
        if (isupper(text[i])) {
            histogram[text[i] - 'A']++;
        } else if (islower(text[i])) {
            histogram[text[i] - 'a']++;
        }
    }
}

/**
 * Computes the Chi-Squared distance between 2 histograms of letter frequencies
 * @param hist1 the first histogram (also used as expected)
 * @param hist2 the second histogram
 * @return the computed distance
 */
double chi_squared_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]) {
    double distance = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        distance = distance + (hist2[i] - hist1[i]) * (hist2[i] - hist1[i]) / hist1[i];
    }
    return distance;
}

//TODO: implement other 2 distance functions

/**
 * Uses frequency analysis to compute the top 3 shifts by lowest distance
 * @param text the text to decipher
 * @param top_shifts the array containing the best 3 shifts
 * @param top_distances the array containing the best 3 distances for their respective shifts
 * @param distance_function the function used to calculate distance
 */
void break_cipher(const char *text, int top_shifts[TOP_N], double top_distances[TOP_N],
                  double (*distance_function)(const double [], const double[]));

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
