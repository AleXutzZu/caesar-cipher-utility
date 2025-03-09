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
    int passed_chi[3] = {0}, passed_cosine[3] = {0}, passed_euclidean[3] = {0};

    while (fscanf(input, "%d %[^\n]", &actual_shift, text) == 2) {
        total_tests++;
        double top_distances[TOP_N];
        int top_shifts[TOP_N];

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, chi_squared_distance);

        for (int i = 0; i < TOP_N; ++i) {
            int reverse_shift = 26 - top_shifts[i];
            if (reverse_shift == actual_shift) passed_chi[i]++;
        }

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, cosine_distance);
        for (int i = 0; i < TOP_N; ++i) {
            int reverse_shift = 26 - top_shifts[i];
            if (reverse_shift == actual_shift) passed_cosine[i]++;
        }

        break_cipher(text, top_shifts, top_distances, reference_distribution_histogram, euclidean_distance);
        for (int i = 0; i < TOP_N; ++i) {
            int reverse_shift = 26 - top_shifts[i];
            if (reverse_shift == actual_shift) passed_euclidean[i]++;
        }
    }
    printf("Total tests: %d\n", total_tests);
    printf("===Chi Stats===\n");
    double total_percent = 0;
    for (int i = 0; i < TOP_N; ++i) {
        double percent = passed_chi[i] * 100.0 / total_tests;
        total_percent += percent;
        printf("Passed #%d guess: %d (%.2lf%%)\n", i + 1, passed_chi[i], percent);
    }
    printf("Total %%: %2.lf%%\n", total_percent);

    printf("===Cosine Stats===\n");
    total_percent = 0;
    for (int i = 0; i < TOP_N; ++i) {
        double percent = passed_cosine[i] * 100.0 / total_tests;
        total_percent += percent;
        printf("Passed #%d guess: %d (%.2lf%%)\n", i + 1, passed_cosine[i], percent);
    }
    printf("Total %%: %2.lf%%\n", total_percent);

    printf("===Euclidean Stats===\n");
    total_percent = 0;
    for (int i = 0; i < TOP_N; ++i) {
        double percent = passed_euclidean[i] * 100.0 / total_tests;
        total_percent += percent;
        printf("Passed #%d guess: %d (%.2lf%%)\n", i + 1, passed_euclidean[i], percent);
    }
    printf("Total %%: %2.lf%%\n", total_percent);
    return 0;
}