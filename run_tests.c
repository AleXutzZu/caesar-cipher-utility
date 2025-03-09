#include <stdio.h>
#include "caesar.h"
#include "io_functions.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments supplied!");
        return -1;
    }
    double reference_distribution_histogram[ALPHABET_SIZE];
    read_distribution("distribution.txt", reference_distribution_histogram);

    printf("Running all 3 distance methods on the sample tests...\n");
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "An unknown error has occurred when opening the file.");
        return -1;
    }
    int actual_shift;
    char text[MAX_SIZE + 1];

    int total_tests = 0;
    int passed_chi = 0, passed_cosine = 0, passed_euclidean = 0;
    while (fscanf(input, "%d %[^\n]", &actual_shift, text) == 2) {
        total_tests++;
        double top_distances[TOP_N];
        int top_shifts[TOP_N];

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, chi_squared_distance);

        int reverse_shift = 26 - top_shifts[0];
        if (reverse_shift == actual_shift) passed_chi++;

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, cosine_distance);
        reverse_shift = 26 - top_shifts[0];
        if (reverse_shift == actual_shift) passed_cosine++;

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, euclidean_distance);
        reverse_shift = 26 - top_shifts[0];
        if (reverse_shift == actual_shift) passed_euclidean++;
    }
    printf("Total tests: %d\n", total_tests);
    printf("Passed for Chi: %d (%.2lf%%)\n", passed_chi, passed_chi * 100.0 / total_tests);
    printf("Passed for Cosine: %d (%.2lf%%)\n", passed_cosine, passed_cosine * 100.0 / total_tests);
    printf("Passed for Euclidean: %d (%.2lf%%)\n", passed_euclidean, passed_euclidean * 100.0 / total_tests);
    return 0;
}