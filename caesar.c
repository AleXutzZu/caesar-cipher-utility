#include "caesar.h"
#include <math.h>
#include <ctype.h>

void compute_histogram(const char *text, double histogram[ALPHABET_SIZE]) {
    for (unsigned int i = 0; text[i] != '\0'; ++i) {
        if (isupper(text[i])) {
            histogram[text[i] - 'A']++;
        } else if (islower(text[i])) {
            histogram[text[i] - 'a']++;
        }
    }
}


double chi_squared_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]) {
    double distance = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        distance = distance + (hist2[i] - hist1[i]) * (hist2[i] - hist1[i]) / hist1[i];
    }
    return distance;
}

double euclidean_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]) {
    double result = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        result += (hist2[i] - hist1[i]) * (hist2[i] - hist1[i]);
    }
    result = sqrt(result);
    return result;
}

double cosine_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]) {
    double sum_product = 0, sum_reference = 0, sum_compare = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        sum_product += hist1[i] * hist2[i];
        sum_reference += hist1[i] * hist1[i];
        sum_compare += hist2[i] * hist2[i];
    }

    double result = 1 - sum_product / sqrt(sum_compare * sum_reference);
    return result;
}

void shift_text(char *text) {
    for (unsigned int i = 0; text[i] != '\0'; ++i) {
        if (isupper(text[i])) {
            int current_char = text[i] - 'A';
            int next_char = (current_char + 1) % 26;
            text[i] = 'A' + next_char;
        } else if (islower(text[i])) {
            int current_char = text[i] - 'a';
            int next_char = (current_char + 1) % 26;
            text[i] = 'a' + next_char;
        }
    }
}

void break_cipher(const char *text, int top_shifts[TOP_N], double top_distances[TOP_N],
                  double reference_distribution_histogram[ALPHABET_SIZE],
                  double (*distance_function)(const double [], const double[])) {

    for (int i = 0; i < TOP_N; ++i) top_distances[i] = top_shifts[i] = -1;

    for (int shift = 0; shift < 26; ++shift) {
        double cipher_histogram[ALPHABET_SIZE] = {0};
        compute_histogram(text, cipher_histogram);

        double distance = distance_function(reference_distribution_histogram, cipher_histogram);

        for (int i = 0; i < TOP_N; ++i) {
            if (distance < top_distances[i] || top_distances[i] == -1) {
                for (int j = TOP_N - 1; j > i; --j) {
                    top_distances[j] = top_distances[j - 1];
                    top_shifts[j] = top_shifts[j - 1];
                }
                top_distances[i] = distance;
                top_shifts[i] = shift;
                break;
            }
        }
    }
}